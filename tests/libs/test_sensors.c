#include "unity.h"
/* Include libs here */

void setUp(void) {
    /* Set up test here */
}

void tearDown(void) {
    /* Clean up test here */
}

void test_test(void) {
    /**
     * TEST_ASSERT_EQUAL( *expected value* , *function return* )
     * look at unity docs
     */
    TEST_ASSERT_EQUAL(0, 1);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_test);
    return UNITY_END();
}