#include "d_pool.h"
#include "munit/munit.h"
#include <assert.h>

static MunitResult init_and_free(const MunitParameter params[],
                                 void *user_data) {
  assert(params == NULL);
  assert(user_data != NULL);

  DBump bump;
  dbump_init(&bump, 1024);

  munit_assert_ptr_not_null(bump.memory);

  dbump_free(&bump);
  return MUNIT_OK;
}

static MunitResult allocate_memory(const MunitParameter params[],
                                   void *user_data) {

  assert(params == NULL);
  assert(user_data != NULL);

  DBump bump;
  dbump_init(&bump, 128 * 10);

  munit_assert_ptr_not_null(bump.memory);

  void *ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_null(ptr);
  dbump_free(&bump);
  return MUNIT_OK;
}

static MunitResult reset_and_allocate(const MunitParameter params[],
                                      void *user_data) {

  assert(params == NULL);
  assert(user_data != NULL);

  DBump bump;
  dbump_init(&bump, 128 * 3);

  munit_assert_ptr_not_null(bump.memory);

  void *ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);

  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_null(ptr);

  dbump_reset(&bump);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);
  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_not_null(ptr);

  ptr = dbump_alloc(&bump, 128);
  munit_assert_ptr_null(ptr);

  dbump_free(&bump);
  return MUNIT_OK;
}

MunitTest tests[] = {{(char *)"dbump/init_and_free", init_and_free, NULL, NULL,
                      MUNIT_TEST_OPTION_NONE, NULL},
                     {(char *)"dbump/allocate_memory", allocate_memory, NULL,
                      NULL, MUNIT_TEST_OPTION_NONE, NULL},
                     {(char *)"dbump/reset_and_allocate", reset_and_allocate,
                      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"DBump", argc, argv);
}
