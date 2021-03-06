/*
 * Copyright (C) 2013 Kay Sievers
 * Copyright (C) 2013 Greg Kroah-Hartman <gregkh@linuxfoundation.org>
 * Copyright (C) 2013 Linux Foundation
 *
 * kdbus is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 */

#ifndef __KDBUS_MESSAGE_H
#define __KDBUS_MESSAGE_H

#include "internal.h"

struct kdbus_kmsg {
	/* short-cuts for faster lookup */
	u64 notification_type;
	const char *dst_name;
	const char *src_names;
	size_t src_names_len;
	const u64 *bloom;
	unsigned int bloom_size;
	const int *fds;
	unsigned int fds_count;

	/* appended SCM-like metadata */
	struct kdbus_item *meta;
	size_t meta_size;
	size_t meta_allocated_size;

	/* size of PAYLOAD data */
	size_t vecs_size;
	unsigned int vecs_count;
	unsigned int memfds_count;

	/* added metadata flags KDBUS_HELLO_ATTACH_* */
	u64 meta_attached;

	struct kdbus_msg msg;
};

struct kdbus_ep;
struct kdbus_conn;

int kdbus_kmsg_new(size_t extra_size, struct kdbus_kmsg **m);
int kdbus_kmsg_new_from_user(struct kdbus_conn *conn, struct kdbus_msg __user *msg, struct kdbus_kmsg **m);
void kdbus_kmsg_free(struct kdbus_kmsg *kmsg);

int kdbus_kmsg_append_timestamp(struct kdbus_kmsg *kmsg, u64 *now_ns);
int kdbus_kmsg_append_src_names(struct kdbus_kmsg *kmsg,
				struct kdbus_conn *conn);
int kdbus_kmsg_append_cred(struct kdbus_kmsg *kmsg,
			   const struct kdbus_creds *creds);
int kdbus_kmsg_append_meta(struct kdbus_kmsg *kmsg,
			   struct kdbus_conn *conn_src,
			   struct kdbus_conn *conn_dst);
#endif
