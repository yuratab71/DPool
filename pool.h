#ifndef pool_h
#define pool_h

#include <stddef.h>
#include <stdint.h>

typedef union {
  void *next;
  uint8_t *data;
} DNode;

typedef struct {
  DNode *free;
  uint8_t *memory;
} DPool;

void dpool_init_pool(DPool *pool, size_t size, size_t data_size);
void dpool_free_pool(DPool *pool);
void *dpool_alloc(DPool *pool);
void dpool_free(DPool *pool, void *ptr);

#endif
