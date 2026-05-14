#include "munit/munit.h"
#include "pool.h"

#define TEST_POOL_SIZE 128

typedef struct {
  int int_val;
  double double_val;
  float float_val;
  short short_val;
} TestStruct;

MunitResult init_and_free(const MunitParameter params[], void *data) {
  DPool pool;
  dpool_init_pool(&pool, 128, sizeof(TestStruct));

  munit_assert_ptr_not_null(pool.memory);
  dpool_free_pool(&pool);

  return MUNIT_OK;
}

MunitTest tests[] = {
    {"init_and_free", init_and_free, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "DPool Test Suite", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
