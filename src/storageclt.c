/*
  Copyright (c) 2010 Fizians SAS. <http://www.fizians.com>
  This file is part of Rozofs.

  Rozofs is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 3 of the License,
  or (at your option) any later version.

  Rozofs is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see
  <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <errno.h>
#include "log.h"
#include "sproto.h"
#include "rpcclt.h"
#include "storageclt.h"

int storageclt_initialize(storageclt_t * clt) {
    int status = -1;
    DEBUG_FUNCTION;

    clt->status = 0;

    if (rpcclt_initialize(&clt->rpcclt, clt->host, STORAGE_PROGRAM, STORAGE_VERSION, ROZOFS_RPC_BUFFER_SIZE, ROZOFS_RPC_BUFFER_SIZE) != 0) {
        // storageclt_release can change errno
        int xerrno = errno;
        //storageclt_release(clt);
        clt->status = 0;
        errno = xerrno;
        goto out;
    }
    clt->status = 1;

    status = 0;
out:
    return status;
}

// XXX Useless
void storageclt_release(storageclt_t * clt) {
    DEBUG_FUNCTION;
    if (clt && clt->rpcclt.client)
        rpcclt_release(&clt->rpcclt);
}

int storageclt_stat(storageclt_t * clt, sstat_t * st) {
    int status = -1;
    sp_stat_ret_t *ret = 0;
    DEBUG_FUNCTION;

    if (!(clt->rpcclt.client) || !(ret = sp_stat_1(&clt->sid, clt->rpcclt.client))) {
        errno = EPROTO;
        goto out;
    }
    if (ret->status != 0) {
        errno = ret->sp_stat_ret_t_u.error;
        goto out;
    }
    memcpy(st, &ret->sp_stat_ret_t_u.sstat, sizeof (sstat_t));

    status = 0;
out:
    if (ret)
        xdr_free((xdrproc_t) xdr_sp_stat_ret_t, (char *) ret);
    return status;
}

int storageclt_write(storageclt_t * clt, fid_t fid, tid_t tid, bid_t bid,
        uint32_t nrb, const bin_t * bins) {
    int status = -1;
    sp_status_ret_t *ret = 0;
    sp_write_arg_t args;
    DEBUG_FUNCTION;

    args.sid = clt->sid;
    memcpy(args.fid, fid, sizeof (uuid_t));
    args.tid = tid;
    args.bid = bid;
    args.nrb = nrb;
    args.bins.bins_len = nrb * rozofs_psizes[tid] * sizeof (bin_t);
    args.bins.bins_val = (char *) bins;

    if (!(clt->rpcclt.client) || !(ret = sp_write_1(&args, clt->rpcclt.client))) {
        clt->status = 0;
        warning("storageclt_write failed: storage write failed (no response from storage server: %s)", clt->host);
        errno = EPROTO;
        goto out;
    }
    if (ret->status != 0) {
        severe("storageclt_write failed: storage write response failure (%s)",
                strerror(errno));
        errno = ret->sp_status_ret_t_u.error;
        goto out;
    }
    status = 0;
out:
    if (ret)
        xdr_free((xdrproc_t) xdr_sp_status_ret_t, (char *) ret);
    return status;
}

int storageclt_read(storageclt_t * clt, fid_t fid, tid_t tid, bid_t bid,
        uint32_t nrb, bin_t * bins) {
    int status = -1;
    sp_read_ret_t *ret = 0;
    sp_read_arg_t args;
    DEBUG_FUNCTION;

    args.sid = clt->sid;
    memcpy(args.fid, fid, sizeof (fid_t));
    args.tid = tid;
    args.bid = bid;
    args.nrb = nrb;
    if (!(clt->rpcclt.client) || !(ret = sp_read_1(&args, clt->rpcclt.client))) {
        clt->status = 0;
        warning("storageclt_read failed: storage read failed (no response from storage server: %s)", clt->host);
        errno = EPROTO;
        goto out;
    }
    if (ret->status != 0) {
        errno = ret->sp_read_ret_t_u.error;
        severe("storageclt_read failed: storage read response failure (%s)", strerror(errno));
        goto out;
    }
    // XXX ret->sp_read_ret_t_u.bins.bins_len is coherent
    // XXX could we avoid memcpy ??
    memcpy(bins, ret->sp_read_ret_t_u.bins.bins_val,
            ret->sp_read_ret_t_u.bins.bins_len);

    status = 0;
out:
    if (ret)
        xdr_free((xdrproc_t) xdr_sp_read_ret_t, (char *) ret);
    return status;
}


// XXX Never used
int storageclt_truncate(storageclt_t * clt, fid_t fid, tid_t tid, bid_t bid) {
    int status = -1;
    sp_status_ret_t *ret = 0;
    sp_truncate_arg_t args;
    DEBUG_FUNCTION;

    args.sid = clt->sid;
    memcpy(args.fid, fid, sizeof (fid_t));
    args.tid = tid;
    args.bid = bid;
    ret = sp_truncate_1(&args, clt->rpcclt.client);
    if (ret == 0) {
        errno = EPROTO;
        goto out;
    }
    if (ret->status != 0) {
        errno = ret->sp_status_ret_t_u.error;
        goto out;
    }
    status = 0;
out:
    if (ret)
        xdr_free((xdrproc_t) xdr_sp_status_ret_t, (char *) ret);
    return status;
}

int storageclt_remove(storageclt_t * clt, fid_t fid) {
    int status = -1;
    sp_status_ret_t *ret = 0;
    sp_remove_arg_t args;
    DEBUG_FUNCTION;

    args.sid = clt->sid;
    memcpy(args.fid, fid, sizeof (fid_t));
    if (!(clt->rpcclt.client) || !(ret = sp_remove_1(&args, clt->rpcclt.client))) {
        errno = EPROTO;
        goto out;
    }
    if (ret->status != 0) {
        errno = ret->sp_status_ret_t_u.error;
        goto out;
    }
    status = 0;
out:
    if (ret)
        xdr_free((xdrproc_t) xdr_sp_status_ret_t, (char *) ret);
    return status;
}
