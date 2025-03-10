/*
 * Copyright (c) 2016, Linaro Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _UAPI_RPMSG_H_
#define _UAPI_RPMSG_H_

#include <linux/ioctl.h>
#include <linux/types.h>

/**
 * struct rpmsg_endpoint_info - endpoint info representation
 * @name: name of service
 * @src: local address
 * @dst: destination address
 */
struct rpmsg_endpoint_info {
	char name[32];
	__u32 src;
	__u32 dst;
};

/**
 * RPMSG_CREATE_EPT_IOCTL:
 *     Create the endpoint specified by info.name,
 *     updates info.id.
 * RPMSG_DESTROY_EPT_IOCTL:
 *     Destroy the endpoint specified by info.id.
 * RPMSG_REST_EPT_GRP_IOCTL:
 *     Destroy all endpoint belonging to info.name
 * RPMSG_DESTROY_ALL_EPT_IOCTL:
 *     Destroy all endpoint
 */
#define RPMSG_CREATE_EPT_IOCTL	_IOW(0xb5, 0x1, struct rpmsg_endpoint_info)
#define RPMSG_DESTROY_EPT_IOCTL	_IO(0xb5, 0x2)
#define RPMSG_REST_EPT_GRP_IOCTL	_IO(0xb5, 0x3)
#define RPMSG_DESTROY_ALL_EPT_IOCTL	_IO(0xb5, 0x4)

/**
 * struct rpmsg_ctrl_msg - used by rpmsg_master.c
 * @name: user define
 * @id: update by driver
 * @cmd:only can RPMSG_*_IOCTL
 * */
struct rpmsg_ept_info {
	char name[32];
	uint32_t id;
};

#endif
