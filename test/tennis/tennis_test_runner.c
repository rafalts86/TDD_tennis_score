#include "unity/fixture/unity_fixture.h"

TEST_GROUP_RUNNER(tennis)
{
   /* Test cases to run */
   RUN_TEST_CASE(tennis, Player1_point);
   RUN_TEST_CASE(tennis, Player1_gets_two_points);
   RUN_TEST_CASE(tennis, Player1_gets_three_points);
   RUN_TEST_CASE(tennis, Player2_point);
   RUN_TEST_CASE(tennis, Player2_gets_two_points);
   RUN_TEST_CASE(tennis, Player2_gets_three_points);
   RUN_TEST_CASE(tennis, Player1_gets_four_points);
   RUN_TEST_CASE(tennis, Player2_gets_four_points);
   RUN_TEST_CASE(tennis, Player1_gets_gem_Player2_reset_points);
   RUN_TEST_CASE(tennis, Player2_gets_gem_Player1_reset_points);
   RUN_TEST_CASE(tennis, Player1_advantage);
}