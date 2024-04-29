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
   RUN_TEST_CASE(tennis, Player1_wins_after_advantage);
   RUN_TEST_CASE(tennis, Player1_advantage_and_player2_gets_point);
   RUN_TEST_CASE(tennis, Player2_advantage);
   RUN_TEST_CASE(tennis, Player2_wins_after_advantage);
   RUN_TEST_CASE(tennis, Player2_advantage_and_player1_gets_point);
   RUN_TEST_CASE(tennis, Player1_wins_set);
   RUN_TEST_CASE(tennis, Player2_wins_set);
   RUN_TEST_CASE(tennis, Player1_6gems_Player2_5gems_no_set_for_player1);
   RUN_TEST_CASE(tennis, Player1_7gems_Player2_5gems_set_for_player1);
}