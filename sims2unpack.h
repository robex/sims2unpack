#ifndef SIM2UNPACK_H
#define SIM2UNPACK_H

#include <stdint.h>

struct idx_t {
	uint32_t typeid;
	uint32_t grpid;
	uint32_t instid_hi;
	uint32_t instid_lo;
	uint32_t file_off;
	uint32_t file_sz;
};

struct dbpf_t {
	uint32_t magic;
	uint32_t majorv;
	uint32_t minorv;
	uint32_t majoru;
	uint32_t minoru;
	uint32_t flags;
	uint32_t created;
	uint32_t modified;
	uint32_t idx_major;
	uint32_t idx_no;
	uint32_t idx_off;
	uint32_t idx_sz;
	uint32_t hole_no;
	uint32_t hole_off;
	uint32_t hole_sz;
	uint32_t idx_minor;

	struct idx_t *idx;
};

#endif
