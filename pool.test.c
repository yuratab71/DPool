#include "munit/munit.h"
#include "pool.h"
#include <assert.h>
#include <stdlib.h>

#define TEST_POOL_SIZE 128

typedef struct {
  int int_val;
  double double_val;
  float float_val;
  short short_val;
} TestStruct;

static MunitResult init_and_free(const MunitParameter params[],
                                 void *user_data) {
  assert(params == NULL);
  assert(user_data != NULL);

  DPool pool;
  dpool_init_pool(&pool, 4, sizeof(TestStruct));

  munit_assert_ptr_not_null(pool.memory);
  dpool_free_pool(&pool);

  return MUNIT_OK;
}

static MunitResult allocate_and_free(const MunitParameter params[],
                                     void *user_data) {
  assert(params == NULL);
  assert(user_data != NULL);

  DPool pool;
  dpool_init_pool(&pool, 4, sizeof(TestStruct));

  TestStruct *d1 = dpool_alloc(&pool);
  TestStruct *d2 = dpool_alloc(&pool);
  TestStruct *d3 = dpool_alloc(&pool);
  TestStruct *d4 = dpool_alloc(&pool);

  dpool_free(&pool, d1);
  dpool_free(&pool, d2);
  dpool_free(&pool, d3);
  dpool_free(&pool, d4);

  dpool_free_pool(&pool);

  return MUNIT_OK;
}

static MunitResult allocate_more_than_size(const MunitParameter params[],
                                           void *user_data) {
  assert(params == NULL);
  assert(user_data != NULL);

  DPool pool;
  dpool_init_pool(&pool, 4, sizeof(TestStruct));

  TestStruct *d1 = dpool_alloc(&pool);
  TestStruct *d2 = dpool_alloc(&pool);
  TestStruct *d3 = dpool_alloc(&pool);
  TestStruct *d4 = dpool_alloc(&pool);

  munit_assert_ptr_not_null(d1);
  munit_assert_ptr_not_null(d2);
  munit_assert_ptr_not_null(d3);
  munit_assert_ptr_not_null(d4);

  TestStruct *d5 = dpool_alloc(&pool);

  munit_assert_ptr_null(d5);

  dpool_free_pool(&pool);

  return MUNIT_OK;
}

static MunitResult allocate_free_and_allocate(const MunitParameter params[],
                                              void *user_data) {
  assert(params == NULL);
  assert(user_data != NULL);

  DPool pool;
  dpool_init_pool(&pool, 4, sizeof(TestStruct));

  TestStruct *d1 = dpool_alloc(&pool);
  TestStruct *d2 = dpool_alloc(&pool);
  TestStruct *d3 = dpool_alloc(&pool);
  TestStruct *d4 = dpool_alloc(&pool);

  dpool_free(&pool, d1);
  dpool_free(&pool, d2);
  dpool_free(&pool, d3);
  dpool_free(&pool, d4);

  TestStruct *d5 = dpool_alloc(&pool);

  munit_assert_ptr_not_null(d5);

  dpool_free_pool(&pool);

  return MUNIT_OK;
}

static MunitResult allocate_and_compare(const MunitParameter params[],
                                        void *user_data) {
  assert(params == NULL);
  assert(user_data != NULL);

  DPool pool;
  dpool_init_pool(&pool, 4, sizeof(TestStruct));

  TestStruct *d1 = dpool_alloc(&pool);
  TestStruct *d2 = dpool_alloc(&pool);
  TestStruct *d3 = dpool_alloc(&pool);
  TestStruct *d4 = dpool_alloc(&pool);

  munit_assert_ptr_not_equal(d1, d2);
  munit_assert_ptr_not_equal(d1, d3);
  munit_assert_ptr_not_equal(d1, d4);

  munit_assert_ptr_not_equal(d2, d1);
  munit_assert_ptr_not_equal(d2, d3);
  munit_assert_ptr_not_equal(d2, d4);

  munit_assert_ptr_not_equal(d3, d1);
  munit_assert_ptr_not_equal(d3, d2);
  munit_assert_ptr_not_equal(d3, d4);

  munit_assert_ptr_not_equal(d4, d1);
  munit_assert_ptr_not_equal(d4, d2);
  munit_assert_ptr_not_equal(d4, d3);

  dpool_free_pool(&pool);

  return MUNIT_OK;
}

MunitTest tests[] = {
    {(char *)"dpool/init_and_free", init_and_free, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {
        (char *)"dpool/allocate_and_free",
        allocate_and_free,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        (char *)"dpool/allocate_more_than_size",
        allocate_more_than_size,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {(char *)"dpool/allocate_and_compare", allocate_and_compare, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"dpool/allocate_free_and_allocate", allocate_free_and_allocate,
     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"Dpool", argc, argv);
}
