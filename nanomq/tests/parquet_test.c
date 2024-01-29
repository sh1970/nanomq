// #include "core/nng_impl.h"
#include "nng/nng.h"
#include "nng/supplemental/nanolib/parquet.h"
#include "nng/supplemental/nanolib/cvector.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nanomq_test.h"

// #include <nuts.h>

#define DO_IT_IF_NOT_NULL(func, arg1, arg2) \
	if (arg1) {                         \
		func(arg1, arg2);           \
	}

#define FREE_IF_NOT_NULL(free, size) DO_IT_IF_NOT_NULL(nng_free, free, size)

#define DATASIZE 10
#define NUM_KEYS 5
#define STRING_LENGTH 12
static uint64_t keys_test[NUM_KEYS][DATASIZE] = { 
	{ 10, 21, 32, 43, 54, 65, 76, 87, 98, 109 },
	{ 110, 121, 132, 143, 154, 165, 176, 187, 198, 1109 },
	{ 220, 222, 232, 243, 254, 265, 276, 287, 298, 2209 },
	{ 330, 333, 333, 343, 354, 365, 376, 387, 398, 3309 },
	{ 440, 444, 444, 444, 454, 465, 476, 487, 498, 4409 } 
};

static uint64_t find_keys_test[NUM_KEYS] = {
	10, 110, 220, 330, 440
};

static char *filenames[NUM_KEYS] = {
	"/tmp/parquet/ly-10~109.parquet",
	"/tmp/parquet/ly-110~1109.parquet",
	"/tmp/parquet/ly-220~2209.parquet",
	"/tmp/parquet/ly-330~3309.parquet",
	"/tmp/parquet/ly-440~4409.parquet"
};

typedef struct {
	nng_aio *aio;
} work;

uint64_t *
keys_allocate(uint64_t keys[], uint32_t size)
{
	uint32_t  i          = 0;
	uint64_t *keys_alloc = malloc(size * sizeof(uint64_t));
	while (i < size) {
		keys_alloc[i] = keys[i];
		i++;
	}
	return keys_alloc;
}