#ifndef d_pool_h_
#define d_pool_h_

#include <stddef.h>
#include <stdint.h>

typedef union {
  void *next;
  uint8_t *data;
} DNode;

typedef struct {
  DNode *free;
  uint8_t *memory;
  size_t capacity;
} DPool;

/**
 * - Initializes the pool
 * size - how many objects
 * data_size - size of each indiviaual objects
 */
void dpool_init_pool(DPool *pool, size_t size, size_t data_size);
/**
 * - Free the pool
 */
void dpool_free_pool(DPool *pool);
/**
 * - Allocate the indiviaual block of memory, with size that was passed to init
 * function, returns the (void *) pointer
 * If not enough memory returns the NULL
 */
void *dpool_alloc(DPool *pool);
/**
 * Frees the individual object that was allocated before
 */
void dpool_free(DPool *pool, void *ptr);

#define DBUMP_DEFAULT_ALIGNMENT 16

typedef struct {
  void *memory;
  uintptr_t offset;
  size_t capacity;
} DBump;

void dbump_init(DBump *bump, size_t size);
void *dbump_alloc(DBump *bump, size_t size);
void dbump_reset(DBump *bump);
void dbump_free(DBump *bump);

#endif
