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
   RUN_TEST_CASE(tennis, Player1_gets_game_Player2_reset_points);
   RUN_TEST_CASE(tennis, Player2_gets_game_Player1_reset_points);
   RUN_TEST_CASE(tennis, Player1_advantage);
   RUN_TEST_CASE(tennis, Player1_wins_after_advantage);
   RUN_TEST_CASE(tennis, Player1_advantage_and_player2_gets_point);
   RUN_TEST_CASE(tennis, Player2_advantage);
   RUN_TEST_CASE(tennis, Player2_wins_after_advantage);
   RUN_TEST_CASE(tennis, Player2_advantage_and_player1_gets_point);
   RUN_TEST_CASE(tennis, Player1_wins_set);
   RUN_TEST_CASE(tennis, Player2_wins_set);
   RUN_TEST_CASE(tennis, Player1_6games_Player2_5games_no_set_for_player1);
   RUN_TEST_CASE(tennis, Player1_7games_Player2_5games_set_for_player1);
   RUN_TEST_CASE(tennis, Player1_6games_Player2_6games_tie_break);
   RUN_TEST_CASE(tennis, Player1_wins_point_during_tie_break);
   RUN_TEST_CASE(tennis, Player1_wins_set_after_tie_break);
   RUN_TEST_CASE(tennis, Player1_wins_set_after_tie_break_new_status_regular);
   RUN_TEST_CASE(tennis, Reset_games_and_points_after_set_win);
   RUN_TEST_CASE(tennis, Tie_break_Player1_wins_7_points_Player2_wins_6_point_no_set_win);
   RUN_TEST_CASE(tennis, Tie_break_Player1_wins_after_advantage);
   RUN_TEST_CASE(tennis, Tie_break_Player1_advantage_and_player2_wins_point);
   RUN_TEST_CASE(tennis, Tie_break_Player2_wins_7_points_Player1_wins_6_point_no_set_win);
   RUN_TEST_CASE(tennis, Tie_break_Player2_wins_after_advantage);
   RUN_TEST_CASE(tennis, Tie_break_Player2_advantage_and_player1_wins_point);
   RUN_TEST_CASE(tennis, Read_games_from_score_table_after_init);
   RUN_TEST_CASE(tennis, Save_games_to_score_table_after_set_win);
   RUN_TEST_CASE(tennis, Save_games_to_score_table_after_second_set_win);
   RUN_TEST_CASE(tennis, Save_games_to_score_table_after_third_set_win);
   RUN_TEST_CASE(tennis, Save_games_to_score_table_after_win_in_tie_break);
   RUN_TEST_CASE(tennis, Player1_wins_state_match_ended);
   RUN_TEST_CASE(tennis, Player2_wins_state_match_ended);
   RUN_TEST_CASE(tennis, Match_ended_no_more_points_for_players);
   RUN_TEST_CASE(tennis, Player1_wins_winner_is_PLAYER1);
   RUN_TEST_CASE(tennis, Player2_wins_winner_is_PLAYER2);
   RUN_TEST_CASE(tennis, Player1_is_player_to_serve_after_init);
   RUN_TEST_CASE(tennis, Player2_is_player_to_serve_after_first_game);
   RUN_TEST_CASE(tennis, Player1_is_player_to_serve_after_second_game);
   RUN_TEST_CASE(tennis, Player_NONE_is_player_to_serve_after_end_of_match);
   RUN_TEST_CASE(tennis, EVENT_NONE_after_init);
   RUN_TEST_CASE(tennis, MATCH_POINT_event);
   RUN_TEST_CASE(tennis, MATCH_POINT_40_0_and_opposte_player_gets_point);
   RUN_TEST_CASE(tennis, MATCH_POINT_40_30_and_opposte_player_gets_point);
   RUN_TEST_CASE(tennis, MATCH_POINT_during_tie_break_5_5_and_player_gets_point);
}