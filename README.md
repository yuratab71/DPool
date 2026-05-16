# - DPool:

Simple object pool and arena(bump) allocators, for my personal needs
Single .c file and .h file

# - Usage:
- Object Pool
```c
#include "d_pool.h"

DPool pool;

dpool_init_pool(&pool, 128, sizeof(YourStruct));

YourStruct *data = dpool_alloc(&pool);

// ...

dpool_free(data);

dpool_free_pool(&pool);

```
- Bump allocator, use 16 byte alignment
```c
#include "d_pool.h"

DBump bump;
dbump_init(&bump, 128 * 3);

YourStruct *data = dbump_alloc(&pool, sizeof(YourStruct));

dbump_reset(&bump);

dbump_free(&bump);

// ...

dpool_free(data);

dpool_free_pool(&pool);
```
