/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _EPROTO_H_RPCGEN
#define _EPROTO_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#include "rozo.h"

typedef u_char ep_uuid_t[ROZO_UUID_SIZE];

typedef char *ep_name_t;

typedef char *ep_path_t;

typedef char ep_link_t[ROZO_PATH_MAX];

typedef char ep_host_t[ROZO_HOSTNAME_MAX];

enum ep_status_t {
	EP_SUCCESS = 0,
	EP_FAILURE = 1,
};
typedef enum ep_status_t ep_status_t;

struct ep_status_ret_t {
	ep_status_t status;
	union {
		int error;
	} ep_status_ret_t_u;
};
typedef struct ep_status_ret_t ep_status_ret_t;

struct ep_storage_t {
	uint16_t sid;
	ep_host_t host;
};
typedef struct ep_storage_t ep_storage_t;

struct ep_cluster_t {
	uint16_t cid;
	uint8_t storages_nb;
	ep_storage_t storages[ROZO_STORAGES_MAX];
};
typedef struct ep_cluster_t ep_cluster_t;

struct ep_volume_t {
	uint32_t eid;
	ep_uuid_t rfid;
	int rl;
	uint8_t clusters_nb;
	ep_cluster_t clusters[ROZO_CLUSTERS_MAX];
};
typedef struct ep_volume_t ep_volume_t;

struct ep_mount_ret_t {
	ep_status_t status;
	union {
		ep_volume_t volume;
		int error;
	} ep_mount_ret_t_u;
};
typedef struct ep_mount_ret_t ep_mount_ret_t;

struct ep_mattr_t {
	ep_uuid_t fid;
	uint16_t cid;
	uint16_t sids[ROZO_SAFE_MAX];
	uint32_t mode;
	uint16_t nlink;
	uint64_t ctime;
	uint64_t atime;
	uint64_t mtime;
	uint64_t size;
};
typedef struct ep_mattr_t ep_mattr_t;

struct ep_mattr_ret_t {
	ep_status_t status;
	union {
		ep_mattr_t attrs;
		int error;
	} ep_mattr_ret_t_u;
};
typedef struct ep_mattr_ret_t ep_mattr_ret_t;

struct ep_lookup_arg_t {
	uint32_t eid;
	ep_uuid_t parent;
	ep_name_t name;
};
typedef struct ep_lookup_arg_t ep_lookup_arg_t;

struct ep_mfile_arg_t {
	uint32_t eid;
	ep_uuid_t fid;
};
typedef struct ep_mfile_arg_t ep_mfile_arg_t;

struct ep_statfs_t {
	uint16_t bsize;
	uint64_t blocks;
	uint64_t bfree;
	uint64_t files;
	uint64_t ffree;
	uint16_t namemax;
};
typedef struct ep_statfs_t ep_statfs_t;

struct ep_statfs_ret_t {
	ep_status_t status;
	union {
		ep_statfs_t stat;
		int error;
	} ep_statfs_ret_t_u;
};
typedef struct ep_statfs_ret_t ep_statfs_ret_t;

struct ep_setattr_arg_t {
	uint32_t eid;
	ep_mattr_t attrs;
};
typedef struct ep_setattr_arg_t ep_setattr_arg_t;

struct ep_getattr_ret_t {
	ep_status_t status;
	union {
		ep_mattr_t attrs;
		int error;
	} ep_getattr_ret_t_u;
};
typedef struct ep_getattr_ret_t ep_getattr_ret_t;

struct ep_readlink_ret_t {
	ep_status_t status;
	union {
		ep_link_t link;
		int error;
	} ep_readlink_ret_t_u;
};
typedef struct ep_readlink_ret_t ep_readlink_ret_t;

struct ep_mknod_arg_t {
	uint32_t eid;
	ep_uuid_t parent;
	ep_name_t name;
	uint32_t mode;
};
typedef struct ep_mknod_arg_t ep_mknod_arg_t;

struct ep_mkdir_arg_t {
	uint32_t eid;
	ep_uuid_t parent;
	ep_name_t name;
	uint32_t mode;
};
typedef struct ep_mkdir_arg_t ep_mkdir_arg_t;

struct ep_symlink_arg_t {
	uint32_t eid;
	ep_uuid_t target;
	ep_uuid_t link_parent;
	ep_name_t link_name;
};
typedef struct ep_symlink_arg_t ep_symlink_arg_t;

typedef struct ep_child_t *ep_children_t;

struct ep_child_t {
	ep_name_t name;
	ep_children_t next;
};
typedef struct ep_child_t ep_child_t;

struct ep_readdir_ret_t {
	ep_status_t status;
	union {
		ep_children_t children;
		int error;
	} ep_readdir_ret_t_u;
};
typedef struct ep_readdir_ret_t ep_readdir_ret_t;

struct ep_rename_arg_t {
	uint32_t eid;
	ep_uuid_t from;
	ep_uuid_t to_parent;
	ep_name_t to_name;
};
typedef struct ep_rename_arg_t ep_rename_arg_t;

struct ep_io_arg_t {
	uint32_t eid;
	ep_uuid_t fid;
	uint64_t offset;
	uint32_t length;
};
typedef struct ep_io_arg_t ep_io_arg_t;

struct ep_write_block_arg_t {
	uint32_t eid;
	ep_uuid_t fid;
	uint64_t bid;
	uint32_t nrb;
	uint16_t dist;
};
typedef struct ep_write_block_arg_t ep_write_block_arg_t;

struct ep_read_block_arg_t {
	uint32_t eid;
	ep_uuid_t fid;
	uint64_t bid;
	uint32_t nrb;
};
typedef struct ep_read_block_arg_t ep_read_block_arg_t;

struct ep_read_block_ret_t {
	ep_status_t status;
	union {
		struct {
			u_int dist_len;
			uint16_t *dist_val;
		} dist;
		int error;
	} ep_read_block_ret_t_u;
};
typedef struct ep_read_block_ret_t ep_read_block_ret_t;

struct ep_io_ret_t {
	ep_status_t status;
	union {
		int64_t length;
		int error;
	} ep_io_ret_t_u;
};
typedef struct ep_io_ret_t ep_io_ret_t;

#define EXPORT_PROGRAM 0x20000005
#define EXPORT_VERSION 1

#if defined(__STDC__) || defined(__cplusplus)
#define EP_NULL 0
extern  void * ep_null_1(void *, CLIENT *);
extern  void * ep_null_1_svc(void *, struct svc_req *);
#define EP_MOUNT 1
extern  ep_mount_ret_t * ep_mount_1(ep_path_t *, CLIENT *);
extern  ep_mount_ret_t * ep_mount_1_svc(ep_path_t *, struct svc_req *);
#define EP_UMOUNT 2
extern  ep_status_ret_t * ep_umount_1(uint32_t *, CLIENT *);
extern  ep_status_ret_t * ep_umount_1_svc(uint32_t *, struct svc_req *);
#define EP_STATFS 3
extern  ep_statfs_ret_t * ep_statfs_1(uint32_t *, CLIENT *);
extern  ep_statfs_ret_t * ep_statfs_1_svc(uint32_t *, struct svc_req *);
#define EP_LOOKUP 4
extern  ep_mattr_ret_t * ep_lookup_1(ep_lookup_arg_t *, CLIENT *);
extern  ep_mattr_ret_t * ep_lookup_1_svc(ep_lookup_arg_t *, struct svc_req *);
#define EP_GETATTR 5
extern  ep_mattr_ret_t * ep_getattr_1(ep_mfile_arg_t *, CLIENT *);
extern  ep_mattr_ret_t * ep_getattr_1_svc(ep_mfile_arg_t *, struct svc_req *);
#define EP_SETATTR 6
extern  ep_mattr_ret_t * ep_setattr_1(ep_setattr_arg_t *, CLIENT *);
extern  ep_mattr_ret_t * ep_setattr_1_svc(ep_setattr_arg_t *, struct svc_req *);
#define EP_READLINK 7
extern  ep_readlink_ret_t * ep_readlink_1(ep_mfile_arg_t *, CLIENT *);
extern  ep_readlink_ret_t * ep_readlink_1_svc(ep_mfile_arg_t *, struct svc_req *);
#define EP_MKNOD 8
extern  ep_mattr_ret_t * ep_mknod_1(ep_mknod_arg_t *, CLIENT *);
extern  ep_mattr_ret_t * ep_mknod_1_svc(ep_mknod_arg_t *, struct svc_req *);
#define EP_MKDIR 9
extern  ep_mattr_ret_t * ep_mkdir_1(ep_mkdir_arg_t *, CLIENT *);
extern  ep_mattr_ret_t * ep_mkdir_1_svc(ep_mkdir_arg_t *, struct svc_req *);
#define EP_UNLINK 10
extern  ep_status_ret_t * ep_unlink_1(ep_mfile_arg_t *, CLIENT *);
extern  ep_status_ret_t * ep_unlink_1_svc(ep_mfile_arg_t *, struct svc_req *);
#define EP_RMDIR 11
extern  ep_status_ret_t * ep_rmdir_1(ep_mfile_arg_t *, CLIENT *);
extern  ep_status_ret_t * ep_rmdir_1_svc(ep_mfile_arg_t *, struct svc_req *);
#define EP_SYMLINK 12
extern  ep_mattr_ret_t * ep_symlink_1(ep_symlink_arg_t *, CLIENT *);
extern  ep_mattr_ret_t * ep_symlink_1_svc(ep_symlink_arg_t *, struct svc_req *);
#define EP_RENAME 13
extern  ep_status_ret_t * ep_rename_1(ep_rename_arg_t *, CLIENT *);
extern  ep_status_ret_t * ep_rename_1_svc(ep_rename_arg_t *, struct svc_req *);
#define EP_READDIR 14
extern  ep_readdir_ret_t * ep_readdir_1(ep_mfile_arg_t *, CLIENT *);
extern  ep_readdir_ret_t * ep_readdir_1_svc(ep_mfile_arg_t *, struct svc_req *);
#define EP_READ 15
extern  ep_io_ret_t * ep_read_1(ep_io_arg_t *, CLIENT *);
extern  ep_io_ret_t * ep_read_1_svc(ep_io_arg_t *, struct svc_req *);
#define EP_READ_BLOCK 16
extern  ep_read_block_ret_t * ep_read_block_1(ep_read_block_arg_t *, CLIENT *);
extern  ep_read_block_ret_t * ep_read_block_1_svc(ep_read_block_arg_t *, struct svc_req *);
#define EP_WRITE 17
extern  ep_io_ret_t * ep_write_1(ep_io_arg_t *, CLIENT *);
extern  ep_io_ret_t * ep_write_1_svc(ep_io_arg_t *, struct svc_req *);
#define EP_WRITE_BLOCK 18
extern  ep_status_ret_t * ep_write_block_1(ep_write_block_arg_t *, CLIENT *);
extern  ep_status_ret_t * ep_write_block_1_svc(ep_write_block_arg_t *, struct svc_req *);
#define EP_OPEN 19
extern  ep_status_ret_t * ep_open_1(ep_mfile_arg_t *, CLIENT *);
extern  ep_status_ret_t * ep_open_1_svc(ep_mfile_arg_t *, struct svc_req *);
#define EP_CLOSE 20
extern  ep_status_ret_t * ep_close_1(ep_mfile_arg_t *, CLIENT *);
extern  ep_status_ret_t * ep_close_1_svc(ep_mfile_arg_t *, struct svc_req *);
extern int export_program_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define EP_NULL 0
extern  void * ep_null_1();
extern  void * ep_null_1_svc();
#define EP_MOUNT 1
extern  ep_mount_ret_t * ep_mount_1();
extern  ep_mount_ret_t * ep_mount_1_svc();
#define EP_UMOUNT 2
extern  ep_status_ret_t * ep_umount_1();
extern  ep_status_ret_t * ep_umount_1_svc();
#define EP_STATFS 3
extern  ep_statfs_ret_t * ep_statfs_1();
extern  ep_statfs_ret_t * ep_statfs_1_svc();
#define EP_LOOKUP 4
extern  ep_mattr_ret_t * ep_lookup_1();
extern  ep_mattr_ret_t * ep_lookup_1_svc();
#define EP_GETATTR 5
extern  ep_mattr_ret_t * ep_getattr_1();
extern  ep_mattr_ret_t * ep_getattr_1_svc();
#define EP_SETATTR 6
extern  ep_mattr_ret_t * ep_setattr_1();
extern  ep_mattr_ret_t * ep_setattr_1_svc();
#define EP_READLINK 7
extern  ep_readlink_ret_t * ep_readlink_1();
extern  ep_readlink_ret_t * ep_readlink_1_svc();
#define EP_MKNOD 8
extern  ep_mattr_ret_t * ep_mknod_1();
extern  ep_mattr_ret_t * ep_mknod_1_svc();
#define EP_MKDIR 9
extern  ep_mattr_ret_t * ep_mkdir_1();
extern  ep_mattr_ret_t * ep_mkdir_1_svc();
#define EP_UNLINK 10
extern  ep_status_ret_t * ep_unlink_1();
extern  ep_status_ret_t * ep_unlink_1_svc();
#define EP_RMDIR 11
extern  ep_status_ret_t * ep_rmdir_1();
extern  ep_status_ret_t * ep_rmdir_1_svc();
#define EP_SYMLINK 12
extern  ep_mattr_ret_t * ep_symlink_1();
extern  ep_mattr_ret_t * ep_symlink_1_svc();
#define EP_RENAME 13
extern  ep_status_ret_t * ep_rename_1();
extern  ep_status_ret_t * ep_rename_1_svc();
#define EP_READDIR 14
extern  ep_readdir_ret_t * ep_readdir_1();
extern  ep_readdir_ret_t * ep_readdir_1_svc();
#define EP_READ 15
extern  ep_io_ret_t * ep_read_1();
extern  ep_io_ret_t * ep_read_1_svc();
#define EP_READ_BLOCK 16
extern  ep_read_block_ret_t * ep_read_block_1();
extern  ep_read_block_ret_t * ep_read_block_1_svc();
#define EP_WRITE 17
extern  ep_io_ret_t * ep_write_1();
extern  ep_io_ret_t * ep_write_1_svc();
#define EP_WRITE_BLOCK 18
extern  ep_status_ret_t * ep_write_block_1();
extern  ep_status_ret_t * ep_write_block_1_svc();
#define EP_OPEN 19
extern  ep_status_ret_t * ep_open_1();
extern  ep_status_ret_t * ep_open_1_svc();
#define EP_CLOSE 20
extern  ep_status_ret_t * ep_close_1();
extern  ep_status_ret_t * ep_close_1_svc();
extern int export_program_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_ep_uuid_t (XDR *, ep_uuid_t);
extern  bool_t xdr_ep_name_t (XDR *, ep_name_t*);
extern  bool_t xdr_ep_path_t (XDR *, ep_path_t*);
extern  bool_t xdr_ep_link_t (XDR *, ep_link_t);
extern  bool_t xdr_ep_host_t (XDR *, ep_host_t);
extern  bool_t xdr_ep_status_t (XDR *, ep_status_t*);
extern  bool_t xdr_ep_status_ret_t (XDR *, ep_status_ret_t*);
extern  bool_t xdr_ep_storage_t (XDR *, ep_storage_t*);
extern  bool_t xdr_ep_cluster_t (XDR *, ep_cluster_t*);
extern  bool_t xdr_ep_volume_t (XDR *, ep_volume_t*);
extern  bool_t xdr_ep_mount_ret_t (XDR *, ep_mount_ret_t*);
extern  bool_t xdr_ep_mattr_t (XDR *, ep_mattr_t*);
extern  bool_t xdr_ep_mattr_ret_t (XDR *, ep_mattr_ret_t*);
extern  bool_t xdr_ep_lookup_arg_t (XDR *, ep_lookup_arg_t*);
extern  bool_t xdr_ep_mfile_arg_t (XDR *, ep_mfile_arg_t*);
extern  bool_t xdr_ep_statfs_t (XDR *, ep_statfs_t*);
extern  bool_t xdr_ep_statfs_ret_t (XDR *, ep_statfs_ret_t*);
extern  bool_t xdr_ep_setattr_arg_t (XDR *, ep_setattr_arg_t*);
extern  bool_t xdr_ep_getattr_ret_t (XDR *, ep_getattr_ret_t*);
extern  bool_t xdr_ep_readlink_ret_t (XDR *, ep_readlink_ret_t*);
extern  bool_t xdr_ep_mknod_arg_t (XDR *, ep_mknod_arg_t*);
extern  bool_t xdr_ep_mkdir_arg_t (XDR *, ep_mkdir_arg_t*);
extern  bool_t xdr_ep_symlink_arg_t (XDR *, ep_symlink_arg_t*);
extern  bool_t xdr_ep_children_t (XDR *, ep_children_t*);
extern  bool_t xdr_ep_child_t (XDR *, ep_child_t*);
extern  bool_t xdr_ep_readdir_ret_t (XDR *, ep_readdir_ret_t*);
extern  bool_t xdr_ep_rename_arg_t (XDR *, ep_rename_arg_t*);
extern  bool_t xdr_ep_io_arg_t (XDR *, ep_io_arg_t*);
extern  bool_t xdr_ep_write_block_arg_t (XDR *, ep_write_block_arg_t*);
extern  bool_t xdr_ep_read_block_arg_t (XDR *, ep_read_block_arg_t*);
extern  bool_t xdr_ep_read_block_ret_t (XDR *, ep_read_block_ret_t*);
extern  bool_t xdr_ep_io_ret_t (XDR *, ep_io_ret_t*);

#else /* K&R C */
extern bool_t xdr_ep_uuid_t ();
extern bool_t xdr_ep_name_t ();
extern bool_t xdr_ep_path_t ();
extern bool_t xdr_ep_link_t ();
extern bool_t xdr_ep_host_t ();
extern bool_t xdr_ep_status_t ();
extern bool_t xdr_ep_status_ret_t ();
extern bool_t xdr_ep_storage_t ();
extern bool_t xdr_ep_cluster_t ();
extern bool_t xdr_ep_volume_t ();
extern bool_t xdr_ep_mount_ret_t ();
extern bool_t xdr_ep_mattr_t ();
extern bool_t xdr_ep_mattr_ret_t ();
extern bool_t xdr_ep_lookup_arg_t ();
extern bool_t xdr_ep_mfile_arg_t ();
extern bool_t xdr_ep_statfs_t ();
extern bool_t xdr_ep_statfs_ret_t ();
extern bool_t xdr_ep_setattr_arg_t ();
extern bool_t xdr_ep_getattr_ret_t ();
extern bool_t xdr_ep_readlink_ret_t ();
extern bool_t xdr_ep_mknod_arg_t ();
extern bool_t xdr_ep_mkdir_arg_t ();
extern bool_t xdr_ep_symlink_arg_t ();
extern bool_t xdr_ep_children_t ();
extern bool_t xdr_ep_child_t ();
extern bool_t xdr_ep_readdir_ret_t ();
extern bool_t xdr_ep_rename_arg_t ();
extern bool_t xdr_ep_io_arg_t ();
extern bool_t xdr_ep_write_block_arg_t ();
extern bool_t xdr_ep_read_block_arg_t ();
extern bool_t xdr_ep_read_block_ret_t ();
extern bool_t xdr_ep_io_ret_t ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_EPROTO_H_RPCGEN */
