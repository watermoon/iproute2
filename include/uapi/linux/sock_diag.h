/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __SOCK_DIAG_H__
#define __SOCK_DIAG_H__

#include <linux/types.h>

#define SOCK_DIAG_BY_FAMILY 20
#define SOCK_DESTROY 21

struct sock_diag_req {
	__u8	sdiag_family;
	__u8	sdiag_protocol;
};

// man ss
// 字段解释: https://manpages.courier-mta.org/htmlman7/sock_diag.7.html
// SK_MEMINFO_WMEM_ALLOC 与 SK_MEMINFO_WMEM_QUEUED 区别的解析: https://unix.stackexchange.com/questions/551444/what-is-the-difference-between-sock-sk-wmem-alloc-and-sock-sk-wmem-queued
// 数据流向: app => socket buffer => qdisc queue => NIC TX ring buffer
// 拥塞控制(cwnd 限制)导致数据无法发送会缓存在 socket buffer
enum {
	SK_MEMINFO_RMEM_ALLOC,  // The amount of data in receive queue.
	SK_MEMINFO_RCVBUF,      // The receive socket buffer as set by SO_RCVBUF.
	SK_MEMINFO_WMEM_ALLOC,  // The amount of data in send queue. # qdisc & device queue 占用的内存
	SK_MEMINFO_SNDBUF,      // The send socket buffer as set by SO_SNDBUF.
	SK_MEMINFO_FWD_ALLOC,   // The amount of memory scheduled for future use (TCP only).
	SK_MEMINFO_WMEM_QUEUED, // The amount of data queued by TCP, but not yet sent. // socket buffer 占用的内存 sock.sk_write_queue
	SK_MEMINFO_OPTMEM,      // The amount of memory allocated for the socket's service needs (e.g., socket filter).
	SK_MEMINFO_BACKLOG,     // The amount of packets in the backlog (not yet processed).
	SK_MEMINFO_DROPS,

	SK_MEMINFO_VARS,
};

enum sknetlink_groups {
	SKNLGRP_NONE,
	SKNLGRP_INET_TCP_DESTROY,
	SKNLGRP_INET_UDP_DESTROY,
	SKNLGRP_INET6_TCP_DESTROY,
	SKNLGRP_INET6_UDP_DESTROY,
	__SKNLGRP_MAX,
};
#define SKNLGRP_MAX	(__SKNLGRP_MAX - 1)

enum {
	SK_DIAG_BPF_STORAGE_REQ_NONE,
	SK_DIAG_BPF_STORAGE_REQ_MAP_FD,
	__SK_DIAG_BPF_STORAGE_REQ_MAX,
};

#define SK_DIAG_BPF_STORAGE_REQ_MAX	(__SK_DIAG_BPF_STORAGE_REQ_MAX - 1)

enum {
	SK_DIAG_BPF_STORAGE_REP_NONE,
	SK_DIAG_BPF_STORAGE,
	__SK_DIAG_BPF_STORAGE_REP_MAX,
};

#define SK_DIAB_BPF_STORAGE_REP_MAX	(__SK_DIAG_BPF_STORAGE_REP_MAX - 1)

enum {
	SK_DIAG_BPF_STORAGE_NONE,
	SK_DIAG_BPF_STORAGE_PAD,
	SK_DIAG_BPF_STORAGE_MAP_ID,
	SK_DIAG_BPF_STORAGE_MAP_VALUE,
	__SK_DIAG_BPF_STORAGE_MAX,
};

#define SK_DIAG_BPF_STORAGE_MAX        (__SK_DIAG_BPF_STORAGE_MAX - 1)

#endif /* __SOCK_DIAG_H__ */
