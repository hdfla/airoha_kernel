/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _AIROHA_NPU_XX230V_H
#define _AIROHA_NPU_XX230V_H

#include <linux/build_bug.h>
#include <linux/types.h>

/*
 * Wire layout described by the xx230v EN7523 SDK wifi_mail_type.h,
 * with TCSUPPORT_NPU_WIFI_OFFLOAD enabled on a 32-bit ARM host.
 * Use explicit padding and fixed-width fields, never native unsigned long.
 */
struct airoha_npu_xx230v_counter {
	__le32 tx_count;
	__le32 rx_count_2g[8];
	__le32 rx_count_5g[8];
	__le32 reserved0;
	__le64 rx_bytes_2g[8];
	__le64 rx_bytes_5g[8];
	u8 omac_5g[8];
	u8 omac_2g[8];
	__le32 rx_count;
	__le32 rx_packets_entry[2][128];
	__le32 reserved1;
	__le64 rx_bytes_entry[2][128];
} __packed;

struct airoha_npu_xx230v_mail {
	/* interface ID in bits 3:0, operation in bits 7:4. */
	__le32 control;
	__le32 function;
	union {
		__le32 value;
		struct airoha_npu_xx230v_counter counters;
	} data;
} __packed;

static_assert(sizeof(struct airoha_npu_xx230v_counter) == 3296);
static_assert(sizeof(struct airoha_npu_xx230v_mail) == 3304);

#endif /* _AIROHA_NPU_XX230V_H */
