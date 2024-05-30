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
   RUN_TEST_CASE(tennis, Player1_6gems_Player2_6gems_tie_break);
   RUN_TEST_CASE(tennis, Player1_wins_point_during_tie_break);
   RUN_TEST_CASE(tennis, Player1_wins_set_after_tie_break);
   RUN_TEST_CASE(tennis, Reset_gems_and_points_after_set_win);
   RUN_TEST_CASE(tennis, Tie_break_Player1_wins_7_points_Player2_wins_6_point_no_set_win);
   RUN_TEST_CASE(tennis, Tie_break_Player1_wins_after_advantage);
   RUN_TEST_CASE(tennis, Tie_break_Player1_advantage_and_player2_wins_point);
   RUN_TEST_CASE(tennis, Tie_break_Player2_wins_7_points_Player1_wins_6_point_no_set_win);
   RUN_TEST_CASE(tennis, Tie_break_Player2_wins_after_advantage);
   RUN_TEST_CASE(tennis, Tie_break_Player2_advantage_and_player1_wins_point);
   RUN_TEST_CASE(tennis, Read_gems_from_score_table_after_init);
   RUN_TEST_CASE(tennis, Save_gems_to_score_table_after_set_win);
   RUN_TEST_CASE(tennis, Save_gems_to_score_table_after_second_set_win);
   RUN_TEST_CASE(tennis, Save_gems_to_score_table_after_third_set_win);
}