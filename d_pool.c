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
