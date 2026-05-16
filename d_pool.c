#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "d_pool.h"

void dpool_init_pool(DPool *pool, size_t sz, size_t obj_sz) {
  pool->capacity = sz * obj_sz;
  pool->memory = (uint8_t *)malloc(pool->capacity);

  pool->free = (DNode *)pool->memory;
  for (size_t i = 1; i <= (sz - 1); i++) {
    assert((i * obj_sz) <= (sz * obj_sz));

    DNode *current = pool->free;
    current->next = (DNode *)(pool->memory + (i * obj_sz));
    pool->free = current->next;
  }

  DNode *current = pool->free;
  current->next = NULL;
  pool->free = (DNode *)pool->memory;

  return;
}

void dpool_free_pool(DPool *pool) {
  assert(pool != NULL);
  assert(pool->memory != NULL);

  free(pool->memory);

  return;
}

void *dpool_alloc(DPool *pool) {
  assert(pool != NULL);

  DNode *node = pool->free;
  if (node == NULL) {
    return NULL;
  }
  pool->free = node->next;

  assert((uintptr_t)node >= (uintptr_t)pool->memory &&
         (uintptr_t)node <
             ((uintptr_t)pool->capacity + (uintptr_t)pool->memory));

  return (void *)node;
}

void dpool_free(DPool *pool, void *ptr) {

  assert(ptr != pool->free);
  assert((uintptr_t)pool->memory <= (uintptr_t)ptr);
  assert((uintptr_t)ptr < ((uintptr_t)pool->memory + pool->capacity));

  DNode *node = (DNode *)ptr;
  node->next = pool->free;
  pool->free = node;

  return;
}

void dbump_init(DBump *bump, size_t size) {
  bump->memory = malloc(size);
  bump->capacity = size;
  bump->offset = (uintptr_t)((uint8_t *)bump->memory + size);
}

void *dbump_alloc(DBump *bump, size_t size) {

  bump->offset -= size;
  bump->offset = bump->offset & ~(DBUMP_DEFAULT_ALIGNMENT - 1);
  if ((uintptr_t)bump->offset < (uintptr_t)bump->memory) {
    return NULL;
  }
  return (void *)bump->offset;
}

void dbump_reset(DBump *bump) {
  bump->offset = (uintptr_t)((uint8_t *)bump->memory + bump->capacity);
}

void dbump_free(DBump *bump) { free(bump->memory); }
