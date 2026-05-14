CC = gcc 

CFLAGS = -Include \
	 -Imunit \
	 -std=c99 \
	 -Wall \
	 -Wextra \

DFLAGS = -g -ggdb3 -O0 -fsanitize=undefined -fsanitize=alignment 

Pool: pool.c
	$(CC) $(DFLAGS) pool.c $(CFLAGS) -o pool

Test: pool.test.c
	$(CC) $(DFLAGS) munit/munit.c pool.c pool.test.c $(CFLAGS) -o pooltest
	./pooltest
