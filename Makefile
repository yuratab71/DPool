CC = gcc 

CFLAGS = -Include \
	 -Imunit \
	 -std=c99 \
	 -Wall \
	 -Wextra \

DFLAGS = -g -ggdb3 -O0 -fsanitize=undefined -fsanitize=alignment 

Pool: d_pool.c
	$(CC) $(DFLAGS) d_pool.c $(CFLAGS) -o d_pool

Test: d_pool.test.c
	$(CC) $(DFLAGS) munit/munit.c d_pool.c d_pool.test.c $(CFLAGS) -o d_pooltest
	./d_pooltest
