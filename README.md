# - DPool:

Simple object pool allocator, for my personal needs
Single .c file and .h file

# - Usage:

```c

#include "d_pool.h"

DPool pool;

dpool_init_pool(&pool, 128, sizeof(YourStrcut));

YourStruct *data = dpool_alloc(&pool);

// ...

dpool_free(data);

dpool_free_pool(&pool);

```


