#include "unity/fixture/unity_fixture.h"

TEST_GROUP_RUNNER(tennis)
{
   /* Test cases to run */
   RUN_TEST_CASE(tennis, Player1_point);
   RUN_TEST_CASE(tennis, Player1_get_two_points);
}