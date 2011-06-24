/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "../src/eproto.h"
#include "rozo.h"

bool_t xdr_ep_uuid_t(XDR * xdrs, ep_uuid_t objp) {
    register int32_t *buf;

    if (!xdr_vector
        (xdrs, (char *) objp, ROZO_UUID_SIZE, sizeof (u_char),
         (xdrproc_t) xdr_u_char))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_name_t(XDR * xdrs, ep_name_t * objp) {
    register int32_t *buf;

    if (!xdr_string(xdrs, objp, ROZO_FILENAME_MAX))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_path_t(XDR * xdrs, ep_path_t * objp) {
    register int32_t *buf;

    if (!xdr_string(xdrs, objp, ROZO_PATH_MAX))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_link_t(XDR * xdrs, ep_link_t objp) {
    register int32_t *buf;

    if (!xdr_vector
        (xdrs, (char *) objp, ROZO_PATH_MAX, sizeof (char),
         (xdrproc_t) xdr_char))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_host_t(XDR * xdrs, ep_host_t objp) {
    register int32_t *buf;

    if (!xdr_vector
        (xdrs, (char *) objp, ROZO_HOSTNAME_MAX, sizeof (char),
         (xdrproc_t) xdr_char))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_status_t(XDR * xdrs, ep_status_t * objp) {
    register int32_t *buf;

    if (!xdr_enum(xdrs, (enum_t *) objp))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_status_ret_t(XDR * xdrs, ep_status_ret_t * objp) {
    register int32_t *buf;

    if (!xdr_ep_status_t(xdrs, &objp->status))
        return FALSE;
    switch (objp->status) {
    case EP_FAILURE:
        if (!xdr_int(xdrs, &objp->ep_status_ret_t_u.error))
            return FALSE;
        break;
    default:
        break;
    }
    return TRUE;
}

bool_t xdr_ep_storage_t(XDR * xdrs, ep_storage_t * objp) {
    register int32_t *buf;

    if (!xdr_uint16_t(xdrs, &objp->sid))
        return FALSE;
    if (!xdr_ep_host_t(xdrs, objp->host))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_cluster_t(XDR * xdrs, ep_cluster_t * objp) {
    register int32_t *buf;

    int i;
    if (!xdr_uint16_t(xdrs, &objp->cid))
        return FALSE;
    if (!xdr_uint8_t(xdrs, &objp->storages_nb))
        return FALSE;
    if (!xdr_vector
        (xdrs, (char *) objp->storages, ROZO_STORAGES_MAX,
         sizeof (ep_storage_t), (xdrproc_t) xdr_ep_storage_t))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_volume_t(XDR * xdrs, ep_volume_t * objp) {
    register int32_t *buf;

    int i;
    if (!xdr_uint32_t(xdrs, &objp->eid))
        return FALSE;
    if (!xdr_ep_uuid_t(xdrs, objp->rfid))
        return FALSE;
    if (!xdr_int(xdrs, &objp->rl))
        return FALSE;
    if (!xdr_uint8_t(xdrs, &objp->clusters_nb))
        return FALSE;
    if (!xdr_vector
        (xdrs, (char *) objp->clusters, ROZO_CLUSTERS_MAX,
         sizeof (ep_cluster_t), (xdrproc_t) xdr_ep_cluster_t))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_mount_ret_t(XDR * xdrs, ep_mount_ret_t * objp) {
    register int32_t *buf;

    if (!xdr_ep_status_t(xdrs, &objp->status))
        return FALSE;
    switch (objp->status) {
    case EP_SUCCESS:
        if (!xdr_ep_volume_t(xdrs, &objp->ep_mount_ret_t_u.volume))
            return FALSE;
        break;
    case EP_FAILURE:
        if (!xdr_int(xdrs, &objp->ep_mount_ret_t_u.error))
            return FALSE;
        break;
    default:
        break;
    }
    return TRUE;
}

bool_t xdr_ep_mattr_t(XDR * xdrs, ep_mattr_t * objp) {
    register int32_t *buf;

    int i;
    if (!xdr_ep_uuid_t(xdrs, objp->fid))
        return FALSE;
    if (!xdr_uint16_t(xdrs, &objp->cid))
        return FALSE;
    if (!xdr_vector
        (xdrs, (char *) objp->sids, ROZO_SAFE_MAX, sizeof (uint16_t),
         (xdrproc_t) xdr_uint16_t))
        return FALSE;
    if (!xdr_uint32_t(xdrs, &objp->mode))
        return FALSE;
    if (!xdr_uint16_t(xdrs, &objp->nlink))
        return FALSE;
    if (!xdr_uint64_t(xdrs, &objp->ctime))
        return FALSE;
    if (!xdr_uint64_t(xdrs, &objp->atime))
        return FALSE;
    if (!xdr_uint64_t(xdrs, &objp->mtime))
        return FALSE;
    if (!xdr_uint64_t(xdrs, &objp->size))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_mattr_ret_t(XDR * xdrs, ep_mattr_ret_t * objp) {
    register int32_t *buf;

    if (!xdr_ep_status_t(xdrs, &objp->status))
        return FALSE;
    switch (objp->status) {
    case EP_SUCCESS:
        if (!xdr_ep_mattr_t(xdrs, &objp->ep_mattr_ret_t_u.attrs))
            return FALSE;
        break;
    case EP_FAILURE:
        if (!xdr_int(xdrs, &objp->ep_mattr_ret_t_u.error))
            return FALSE;
        break;
    default:
        break;
    }
    return TRUE;
}

bool_t xdr_ep_lookup_arg_t(XDR * xdrs, ep_lookup_arg_t * objp) {
    register int32_t *buf;

    if (!xdr_uint32_t(xdrs, &objp->eid))
        return FALSE;
    if (!xdr_ep_uuid_t(xdrs, objp->parent))
        return FALSE;
    if (!xdr_ep_name_t(xdrs, &objp->name))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_mfile_arg_t(XDR * xdrs, ep_mfile_arg_t * objp) {
    register int32_t *buf;

    if (!xdr_uint32_t(xdrs, &objp->eid))
        return FALSE;
    if (!xdr_ep_uuid_t(xdrs, objp->fid))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_statfs_t(XDR * xdrs, ep_statfs_t * objp) {
    register int32_t *buf;

    if (!xdr_uint16_t(xdrs, &objp->bsize))
        return FALSE;
    if (!xdr_uint64_t(xdrs, &objp->blocks))
        return FALSE;
    if (!xdr_uint64_t(xdrs, &objp->bfree))
        return FALSE;
    if (!xdr_uint64_t(xdrs, &objp->files))
        return FALSE;
    if (!xdr_uint64_t(xdrs, &objp->ffree))
        return FALSE;
    if (!xdr_uint16_t(xdrs, &objp->namemax))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_statfs_ret_t(XDR * xdrs, ep_statfs_ret_t * objp) {
    register int32_t *buf;

    if (!xdr_ep_status_t(xdrs, &objp->status))
        return FALSE;
    switch (objp->status) {
    case EP_SUCCESS:
        if (!xdr_ep_statfs_t(xdrs, &objp->ep_statfs_ret_t_u.stat))
            return FALSE;
        break;
    case EP_FAILURE:
        if (!xdr_int(xdrs, &objp->ep_statfs_ret_t_u.error))
            return FALSE;
        break;
    default:
        break;
    }
    return TRUE;
}

bool_t xdr_ep_setattr_arg_t(XDR * xdrs, ep_setattr_arg_t * objp) {
    register int32_t *buf;

    if (!xdr_uint32_t(xdrs, &objp->eid))
        return FALSE;
    if (!xdr_ep_mattr_t(xdrs, &objp->attrs))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_getattr_ret_t(XDR * xdrs, ep_getattr_ret_t * objp) {
    register int32_t *buf;

    if (!xdr_ep_status_t(xdrs, &objp->status))
        return FALSE;
    switch (objp->status) {
    case EP_SUCCESS:
        if (!xdr_ep_mattr_t(xdrs, &objp->ep_getattr_ret_t_u.attrs))
            return FALSE;
        break;
    case EP_FAILURE:
        if (!xdr_int(xdrs, &objp->ep_getattr_ret_t_u.error))
            return FALSE;
        break;
    default:
        break;
    }
    return TRUE;
}

bool_t xdr_ep_readlink_ret_t(XDR * xdrs, ep_readlink_ret_t * objp) {
    register int32_t *buf;

    if (!xdr_ep_status_t(xdrs, &objp->status))
        return FALSE;
    switch (objp->status) {
    case EP_SUCCESS:
        if (!xdr_ep_link_t(xdrs, objp->ep_readlink_ret_t_u.link))
            return FALSE;
        break;
    case EP_FAILURE:
        if (!xdr_int(xdrs, &objp->ep_readlink_ret_t_u.error))
            return FALSE;
        break;
    default:
        break;
    }
    return TRUE;
}

bool_t xdr_ep_mknod_arg_t(XDR * xdrs, ep_mknod_arg_t * objp) {
    register int32_t *buf;

    if (!xdr_uint32_t(xdrs, &objp->eid))
        return FALSE;
    if (!xdr_ep_uuid_t(xdrs, objp->parent))
        return FALSE;
    if (!xdr_ep_name_t(xdrs, &objp->name))
        return FALSE;
    if (!xdr_uint32_t(xdrs, &objp->mode))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_mkdir_arg_t(XDR * xdrs, ep_mkdir_arg_t * objp) {
    register int32_t *buf;

    if (!xdr_uint32_t(xdrs, &objp->eid))
        return FALSE;
    if (!xdr_ep_uuid_t(xdrs, objp->parent))
        return FALSE;
    if (!xdr_ep_name_t(xdrs, &objp->name))
        return FALSE;
    if (!xdr_uint32_t(xdrs, &objp->mode))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_symlink_arg_t(XDR * xdrs, ep_symlink_arg_t * objp) {
    register int32_t *buf;

    if (!xdr_uint32_t(xdrs, &objp->eid))
        return FALSE;
    if (!xdr_ep_name_t(xdrs, &objp->link))
        return FALSE;
    if (!xdr_ep_uuid_t(xdrs, objp->parent))
        return FALSE;
    if (!xdr_ep_name_t(xdrs, &objp->name))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_children_t(XDR * xdrs, ep_children_t * objp) {
    register int32_t *buf;

    if (!xdr_pointer
        (xdrs, (char **) objp, sizeof (struct ep_child_t),
         (xdrproc_t) xdr_ep_child_t))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_child_t(XDR * xdrs, ep_child_t * objp) {
    register int32_t *buf;

    if (!xdr_ep_name_t(xdrs, &objp->name))
        return FALSE;
    if (!xdr_ep_children_t(xdrs, &objp->next))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_readdir_ret_t(XDR * xdrs, ep_readdir_ret_t * objp) {
    register int32_t *buf;

    if (!xdr_ep_status_t(xdrs, &objp->status))
        return FALSE;
    switch (objp->status) {
    case EP_SUCCESS:
        if (!xdr_ep_children_t(xdrs, &objp->ep_readdir_ret_t_u.children))
            return FALSE;
        break;
    case EP_FAILURE:
        if (!xdr_int(xdrs, &objp->ep_readdir_ret_t_u.error))
            return FALSE;
        break;
    default:
        break;
    }
    return TRUE;
}

bool_t xdr_ep_rename_arg_t(XDR * xdrs, ep_rename_arg_t * objp) {
    register int32_t *buf;

    if (!xdr_uint32_t(xdrs, &objp->eid))
        return FALSE;
    if (!xdr_ep_uuid_t(xdrs, objp->from))
        return FALSE;
    if (!xdr_ep_uuid_t(xdrs, objp->to_parent))
        return FALSE;
    if (!xdr_ep_name_t(xdrs, &objp->to_name))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_io_arg_t(XDR * xdrs, ep_io_arg_t * objp) {
    register int32_t *buf;

    if (!xdr_uint32_t(xdrs, &objp->eid))
        return FALSE;
    if (!xdr_ep_uuid_t(xdrs, objp->fid))
        return FALSE;
    if (!xdr_uint64_t(xdrs, &objp->offset))
        return FALSE;
    if (!xdr_uint32_t(xdrs, &objp->length))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_write_block_arg_t(XDR * xdrs, ep_write_block_arg_t * objp) {
    register int32_t *buf;

    if (!xdr_uint32_t(xdrs, &objp->eid))
        return FALSE;
    if (!xdr_ep_uuid_t(xdrs, objp->fid))
        return FALSE;
    if (!xdr_uint64_t(xdrs, &objp->bid))
        return FALSE;
    if (!xdr_uint32_t(xdrs, &objp->nrb))
        return FALSE;
    if (!xdr_uint16_t(xdrs, &objp->dist))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_read_block_arg_t(XDR * xdrs, ep_read_block_arg_t * objp) {
    register int32_t *buf;

    if (!xdr_uint32_t(xdrs, &objp->eid))
        return FALSE;
    if (!xdr_ep_uuid_t(xdrs, objp->fid))
        return FALSE;
    if (!xdr_uint64_t(xdrs, &objp->bid))
        return FALSE;
    if (!xdr_uint32_t(xdrs, &objp->nrb))
        return FALSE;
    return TRUE;
}

bool_t xdr_ep_read_block_ret_t(XDR * xdrs, ep_read_block_ret_t * objp) {
    register int32_t *buf;

    if (!xdr_ep_status_t(xdrs, &objp->status))
        return FALSE;
    switch (objp->status) {
    case EP_SUCCESS:
        if (!xdr_array
            (xdrs, (char **) &objp->ep_read_block_ret_t_u.dist.dist_val,
             (u_int *) & objp->ep_read_block_ret_t_u.dist.dist_len, ~0,
             sizeof (uint16_t), (xdrproc_t) xdr_uint16_t))
            return FALSE;
        break;
    case EP_FAILURE:
        if (!xdr_int(xdrs, &objp->ep_read_block_ret_t_u.error))
            return FALSE;
        break;
    default:
        break;
    }
    return TRUE;
}

bool_t xdr_ep_io_ret_t(XDR * xdrs, ep_io_ret_t * objp) {
    register int32_t *buf;

    if (!xdr_ep_status_t(xdrs, &objp->status))
        return FALSE;
    switch (objp->status) {
    case EP_SUCCESS:
        if (!xdr_int64_t(xdrs, &objp->ep_io_ret_t_u.length))
            return FALSE;
        break;
    case EP_FAILURE:
        if (!xdr_int(xdrs, &objp->ep_io_ret_t_u.error))
            return FALSE;
        break;
    default:
        break;
    }
    return TRUE;
}
