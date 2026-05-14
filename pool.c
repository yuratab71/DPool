#include "pool.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void dpool_init_pool(DPool *pool, size_t sz, size_t obj_sz) {
  pool->memory = (uint8_t *)malloc(sz * obj_sz);

  pool->free = (DNode *)pool->memory;
  for (size_t i = 1; i <= sz; i++) {
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
  assert(pool->free != NULL);

  DNode *node = pool->free;
  pool->free = node->next;

  return (void *)node->data;
}

void dpool_free(DPool *pool, void *ptr) {
  assert((uintptr_t)pool->memory < (uintptr_t)ptr);
  assert(ptr != pool->free);

  DNode *node = (DNode *)ptr;
  node->next = pool->free;
  pool->free = node;

  return;
}
