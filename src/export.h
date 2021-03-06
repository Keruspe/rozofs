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

#ifndef _EXPORT_H
#define _EXPORT_H

#include <limits.h>
#include <sys/stat.h>
#include <uuid/uuid.h>

#include "rozofs.h"
#include "htable.h"
#include "dist.h"
#include "volume.h"

typedef struct export {
    eid_t eid; // Export identifier
    //vid_t vid; // Volume identifier
    volume_t *volume;
    char root[PATH_MAX]; // absolute path
    char md5[ROZOFS_MD5_SIZE]; //passwd
    uint64_t squota; // soft quota in blocks
    uint64_t hquota; // hard quota in blocks
    fid_t rfid; // root fid
    char trashname[NAME_MAX]; // trash directory
    list_t mfiles;
    list_t rmfiles;
    pthread_rwlock_t rm_lock;
    htable_t hfids; // fid indexed
    htable_t h_pfids; // parent fid indexed
    uint32_t csize; // nb mfentry_t cached
} export_t;

int export_create(const char *root);

int export_initialize(export_t * e, volume_t *volume, eid_t eid,
        const char *root, const char *md5, uint64_t squota, uint64_t hquota);

void export_release(export_t * e);

int export_stat(export_t * e, estat_t * st);

int export_lookup(export_t * e, fid_t parent, const char *name,
        mattr_t * attrs);

int export_getattr(export_t * e, fid_t fid, mattr_t * attrs);

int export_setattr(export_t * e, fid_t fid, mattr_t * attrs);

int export_readlink(export_t * e, fid_t fid, char link[PATH_MAX]);

int export_link(export_t *e, fid_t inode, fid_t newparent, const char *newname, mattr_t *attrs);

int export_mknod(export_t * e, fid_t parent, const char *name, uint32_t uid,
        uint32_t gid, mode_t mode, mattr_t * attrs);

int export_mkdir(export_t * e, fid_t parent, const char *name, uint32_t uid,
        uint32_t gid, mode_t mode, mattr_t * attrs);

int export_unlink(export_t * e, fid_t pfid, const char *name, fid_t * fid);

int export_rm_bins(export_t * e);

int export_rmdir(export_t * e, fid_t pfid, const char *name, fid_t * fid);

int export_symlink(export_t * e, const char *link, fid_t parent,
        const char *name, mattr_t * attrs);

int export_rename(export_t * e, fid_t pfid, const char *name, fid_t npfid, const char *newname, fid_t * fid);

int64_t export_read(export_t * e, fid_t fid, uint64_t off, uint32_t len);

int export_read_block(export_t * e, fid_t fid, bid_t bid, uint32_t n,
        dist_t * d);

int64_t export_write(export_t * e, fid_t fid, uint64_t off, uint32_t len);

int export_write_block(export_t * e, fid_t fid, bid_t bid, uint32_t n,
        dist_t d);

int export_readdir(export_t * e, fid_t fid, uint64_t cookie, child_t ** children, uint8_t * eof);

int export_open(export_t * e, fid_t fid);

int export_close(export_t * e, fid_t fid);

#endif
