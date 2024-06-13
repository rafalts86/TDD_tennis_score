#include "unity/fixture/unity_fixture.h"

#include "tennis.h"

uint8_t game_win(enum player player)
{
    for(uint8_t i = 0; i < 4; i++)
    {
        tennis_point(player);
    }

    return 1;
}

uint8_t games_win(enum player player, uint8_t no_games)
{
    for(uint8_t i = 0; i < no_games; i++)
    {
        game_win(player);
    }

    return 1;
}

uint8_t set_win(enum player player)
{
    for(uint8_t i = 0; i < 6; i++)
    {
        game_win(player);
    }

    return 1;
}

uint8_t point_win(enum player player, uint8_t current_points)
{
    uint8_t points = 0;

    tennis_point(player);

    switch(current_points)
    {
        case 0:
        case 15:
            points = 15;
            break;
        
        case 30:
            points = 10;
            break;

        case 40:
            points = 0;
            break;
    }

    return points;
}

uint8_t point_win_during_tie_break(enum player player)
{
    tennis_point(player);
    return 1;
}

uint8_t points_win_during_tie_break(enum player player, uint8_t points)
{
    for(uint8_t i = 0; i < points; i++)
    {
        tennis_point(player);
    }

    return points;
}

void tie_break(void)
{
    games_win(PLAYER1, 5);
    games_win(PLAYER2, 5);
    game_win(PLAYER2);
    game_win(PLAYER1);
}

void advantage(enum player player)
{
    if(player == PLAYER1)
    {
        tennis_point(PLAYER2);
        tennis_point(PLAYER2);
        tennis_point(PLAYER2);
        
        tennis_point(PLAYER1);
        tennis_point(PLAYER1);
        tennis_point(PLAYER1);
        tennis_point(PLAYER1);
    }
    else if(player == PLAYER2)
    {
        tennis_point(PLAYER1);
        tennis_point(PLAYER1);
        tennis_point(PLAYER1);

        tennis_point(PLAYER2);
        tennis_point(PLAYER2);
        tennis_point(PLAYER2);
        tennis_point(PLAYER2);
    }
}


TEST_GROUP(tennis);

TEST_SETUP(tennis)
{
    /* Init before every test */
    tennis_init();
}

TEST_TEAR_DOWN(tennis)
{
    /* Cleanup after every test */
}


TEST(tennis, Player1_point)
{
    uint8_t expected = 0;

    expected += point_win(PLAYER1, expected);

    TEST_ASSERT_EQUAL(expected, tennis_get_points(PLAYER1));
}

TEST(tennis, Player1_gets_two_points)
{
    uint8_t expected = 0;

    expected += point_win(PLAYER1, expected);
    expected += point_win(PLAYER1, expected);

    TEST_ASSERT_EQUAL(expected, tennis_get_points(PLAYER1));
}

TEST(tennis, Player1_gets_three_points)
{
    uint8_t expected = 0;

    expected += point_win(PLAYER1, expected);
    expected += point_win(PLAYER1, expected);
    expected += point_win(PLAYER1, expected);

    TEST_ASSERT_EQUAL(expected, tennis_get_points(PLAYER1));
}

TEST(tennis, Player2_point)
{
    uint8_t expected = 0;

    expected += point_win(PLAYER2, expected);
   
    TEST_ASSERT_EQUAL(expected, tennis_get_points(PLAYER2));
}

TEST(tennis, Player2_gets_two_points)
{
    uint8_t expected = 0;

    expected += point_win(PLAYER2, expected);
    expected += point_win(PLAYER2, expected);

    TEST_ASSERT_EQUAL(expected, tennis_get_points(PLAYER2));
}

TEST(tennis, Player2_gets_three_points)
{
    uint8_t expected = 0;

    expected += point_win(PLAYER2, expected);
    expected += point_win(PLAYER2, expected);
    expected += point_win(PLAYER2, expected);

    TEST_ASSERT_EQUAL(expected, tennis_get_points(PLAYER2));
}

TEST(tennis, Player1_gets_four_points)
{
    uint8_t expected_games = 0;
    uint8_t expected_points = 0;

    expected_games += game_win(PLAYER1);

    TEST_ASSERT_EQUAL(expected_points, tennis_get_points(PLAYER1));
    TEST_ASSERT_EQUAL(expected_games, tennis_get_games(PLAYER1));
}

TEST(tennis, Player2_gets_four_points)
{
    uint8_t expected_games = 0;
    uint8_t expected_points = 0;

    expected_games += game_win(PLAYER2);

    TEST_ASSERT_EQUAL(expected_points, tennis_get_points(PLAYER2));
    TEST_ASSERT_EQUAL(expected_games, tennis_get_games(PLAYER2));
}

TEST(tennis, Player1_gets_game_Player2_reset_points)
{
    uint8_t expected_points = 0;
   
    tennis_point(PLAYER2);
    game_win(PLAYER1);

    TEST_ASSERT_EQUAL(expected_points, tennis_get_points(PLAYER2));
}

TEST(tennis, Player2_gets_game_Player1_reset_points)
{
    uint8_t expected_points = 0;

    tennis_point(PLAYER1);
    game_win(PLAYER2);

    TEST_ASSERT_EQUAL(expected_points, tennis_get_points(PLAYER1));
}

TEST(tennis, Player1_advantage)
{
    advantage(PLAYER1);

    TEST_ASSERT_EQUAL(true, tennis_is_advantage(PLAYER1));
}

TEST(tennis, Player1_wins_after_advantage)
{
    uint8_t expectet_games = 1;

    advantage(PLAYER1);
    tennis_point(PLAYER1);

    TEST_ASSERT_EQUAL(false, tennis_is_advantage(PLAYER1));
    TEST_ASSERT_EQUAL(expectet_games, tennis_get_games(PLAYER1));
}

TEST(tennis, Player1_advantage_and_player2_gets_point)
{
    uint8_t expectet_games = 0;
    uint8_t expectet_points = 40;

    advantage(PLAYER1);
    tennis_point(PLAYER2);

    TEST_ASSERT_EQUAL(false, tennis_is_advantage(PLAYER1));
    TEST_ASSERT_EQUAL(expectet_games, tennis_get_games(PLAYER1));
    TEST_ASSERT_EQUAL(expectet_points, tennis_get_points(PLAYER1));
    TEST_ASSERT_EQUAL(expectet_points, tennis_get_points(PLAYER2));
}

TEST(tennis, Player2_advantage)
{
    advantage(PLAYER2);

    TEST_ASSERT_EQUAL(true, tennis_is_advantage(PLAYER2));
}

TEST(tennis, Player2_wins_after_advantage)
{
    uint8_t expectet_games = 1;

    advantage(PLAYER2);
    tennis_point(PLAYER2);

    TEST_ASSERT_EQUAL(false, tennis_is_advantage(PLAYER2));
    TEST_ASSERT_EQUAL(expectet_games, tennis_get_games(PLAYER2));
}

TEST(tennis, Player2_advantage_and_player1_gets_point)
{
    uint8_t expectet_games = 0;
    uint8_t expectet_points = 40;

    advantage(PLAYER2);
    tennis_point(PLAYER1);

    TEST_ASSERT_EQUAL(false, tennis_is_advantage(PLAYER2));
    TEST_ASSERT_EQUAL(expectet_games, tennis_get_games(PLAYER2));
    TEST_ASSERT_EQUAL(expectet_points, tennis_get_points(PLAYER2));
    TEST_ASSERT_EQUAL(expectet_points, tennis_get_points(PLAYER1));
}

TEST(tennis, Player1_wins_set)
{
    uint8_t expected_sets = 0;

    expected_sets += set_win(PLAYER1);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER1));
}

TEST(tennis, Player2_wins_set)
{
    uint8_t expected_sets = 0;

    expected_sets += set_win(PLAYER2);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER2));
}

TEST(tennis, Player1_6games_Player2_5games_no_set_for_player1)
{
    uint8_t expected_sets = 0;

    games_win(PLAYER1, 5);
    games_win(PLAYER2, 5);
    game_win(PLAYER1);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER1));
}

TEST(tennis, Player1_7games_Player2_5games_set_for_player1)
{
    uint8_t expected_sets = 1;

    games_win(PLAYER1, 5);
    games_win(PLAYER2, 5);
    
    games_win(PLAYER1, 2);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER1));
}

TEST(tennis, Player1_6games_Player2_6games_tie_break)
{
    game_state_t expected_state = TIE_BREAK;

    tie_break();

    TEST_ASSERT_EQUAL(expected_state, tennis_get_state());
}

TEST(tennis, Player1_wins_point_during_tie_break)
{
    uint8_t expected_points = 0;

    tie_break();

    expected_points += point_win_during_tie_break(PLAYER1);
    
    TEST_ASSERT_EQUAL(expected_points, tennis_get_points(PLAYER1));
}

TEST(tennis, Player1_wins_set_after_tie_break)
{
    uint8_t expected_sets = 1;

    tie_break();

    for(int i = 0; i < 7; i++)
    {
        point_win_during_tie_break(PLAYER1);
    }
    
    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER1));
}

TEST(tennis, Player1_wins_set_after_tie_break_new_status_regular)
{
    tie_break();

    for(int i = 0; i < 7; i++)
    {
        point_win_during_tie_break(PLAYER1);
    }
    
    TEST_ASSERT_EQUAL(REGULAR, tennis_get_state());
}

TEST(tennis, Reset_games_and_points_after_set_win)
{
    uint8_t expected_games = 0;
    uint8_t expected_points = 0;
    uint8_t expected_sets = 1;

    games_win(PLAYER1, 5);
    games_win(PLAYER2, 5);

    games_win(PLAYER1, 2);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER1));
    TEST_ASSERT_EQUAL(expected_games, tennis_get_games(PLAYER1));
    TEST_ASSERT_EQUAL(expected_games, tennis_get_games(PLAYER2));
    TEST_ASSERT_EQUAL(expected_points, tennis_get_points(PLAYER1));
    TEST_ASSERT_EQUAL(expected_points, tennis_get_points(PLAYER2));
}

TEST(tennis, Tie_break_Player1_wins_7_points_Player2_wins_6_point_no_set_win)
{
    uint8_t expected_sets = 0;
    uint8_t expected_advantage = true;

    tie_break();

    points_win_during_tie_break(PLAYER1, 5);
    points_win_during_tie_break(PLAYER2, 5);

    points_win_during_tie_break(PLAYER1, 1);
    points_win_during_tie_break(PLAYER2, 1);

    points_win_during_tie_break(PLAYER1, 1);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER1));
    TEST_ASSERT_EQUAL(expected_advantage, tennis_is_advantage(PLAYER1));
}

TEST(tennis, Tie_break_Player1_wins_after_advantage)
{
    uint8_t expected_points_player1 = 0;
    uint8_t expected_points_player2 = 0;
    uint8_t expected_sets = 1;
    uint8_t expected_advantage = false;

    tie_break();

    expected_points_player1 += points_win_during_tie_break(PLAYER1, 5);
    expected_points_player2 += points_win_during_tie_break(PLAYER2, 5);

    expected_points_player1 += points_win_during_tie_break(PLAYER1, 1);
    expected_points_player2 += points_win_during_tie_break(PLAYER2, 1);

    expected_points_player1 += points_win_during_tie_break(PLAYER1, 1);
    expected_points_player2 += points_win_during_tie_break(PLAYER2, 1);

    expected_points_player1 += points_win_during_tie_break(PLAYER1, 1);
    expected_points_player1 += points_win_during_tie_break(PLAYER1, 1);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER1));
    TEST_ASSERT_EQUAL(expected_advantage, tennis_is_advantage(PLAYER1));
}

TEST(tennis, Tie_break_Player1_advantage_and_player2_wins_point)
{
    uint8_t expected_sets = 0;
    uint8_t expected_advantage = false;

    tie_break();

    points_win_during_tie_break(PLAYER1, 5);
    points_win_during_tie_break(PLAYER2, 5);

    points_win_during_tie_break(PLAYER1, 1);
    points_win_during_tie_break(PLAYER2, 1);

    points_win_during_tie_break(PLAYER1, 1);
    points_win_during_tie_break(PLAYER2, 1);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER1));
    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER2));
    TEST_ASSERT_EQUAL(expected_advantage, tennis_is_advantage(PLAYER1));
    TEST_ASSERT_EQUAL(expected_advantage, tennis_is_advantage(PLAYER2));
}

TEST(tennis, Tie_break_Player2_wins_7_points_Player1_wins_6_point_no_set_win)
{
    uint8_t expected_sets = 0;
    uint8_t expected_advantage = true;

    tie_break();

    points_win_during_tie_break(PLAYER1, 5);
    points_win_during_tie_break(PLAYER2, 5);

    points_win_during_tie_break(PLAYER1, 1);
    points_win_during_tie_break(PLAYER2, 1);

    points_win_during_tie_break(PLAYER2, 1);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER1));
    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER2));
    TEST_ASSERT_EQUAL(expected_advantage, tennis_is_advantage(PLAYER2));
}

TEST(tennis, Tie_break_Player2_wins_after_advantage)
{
    uint8_t expected_points_player1 = 0;
    uint8_t expected_points_player2 = 0;
    uint8_t expected_sets = 1;
    uint8_t expected_advantage = false;

    tie_break();

    expected_points_player1 += points_win_during_tie_break(PLAYER1, 5);
    expected_points_player2 += points_win_during_tie_break(PLAYER2, 5);
    expected_points_player1 += points_win_during_tie_break(PLAYER1, 1);
    expected_points_player2 += points_win_during_tie_break(PLAYER2, 1);
    expected_points_player1 += points_win_during_tie_break(PLAYER1, 1);
    expected_points_player2 += points_win_during_tie_break(PLAYER2, 1);
    expected_points_player2 += points_win_during_tie_break(PLAYER2, 2);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER2));
    TEST_ASSERT_EQUAL(expected_advantage, tennis_is_advantage(PLAYER2));
}

TEST(tennis, Tie_break_Player2_advantage_and_player1_wins_point)
{
    uint8_t expected_sets = 0;
    uint8_t expected_advantage = false;

    tie_break();
   
    points_win_during_tie_break(PLAYER1, 5);
    points_win_during_tie_break(PLAYER2, 5);
    points_win_during_tie_break(PLAYER1, 1);
    points_win_during_tie_break(PLAYER2, 1);
    points_win_during_tie_break(PLAYER2, 1);
    points_win_during_tie_break(PLAYER1, 1);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER1));
    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER2));
    TEST_ASSERT_EQUAL(expected_advantage, tennis_is_advantage(PLAYER1));
    TEST_ASSERT_EQUAL(expected_advantage, tennis_is_advantage(PLAYER2));
}

TEST(tennis, Read_games_from_score_table_after_init)
{
    uint8_t player1_expected_games = 0;
    uint8_t player2_expected_games = 0;

    TEST_ASSERT_EQUAL(player1_expected_games, tennis_get_score_table_games(PLAYER1, 1));
    TEST_ASSERT_EQUAL(player2_expected_games, tennis_get_score_table_games(PLAYER2, 1));
    TEST_ASSERT_EQUAL(player1_expected_games, tennis_get_score_table_games(PLAYER1, 2));
    TEST_ASSERT_EQUAL(player2_expected_games, tennis_get_score_table_games(PLAYER2, 2));
    TEST_ASSERT_EQUAL(player1_expected_games, tennis_get_score_table_games(PLAYER1, 3));
    TEST_ASSERT_EQUAL(player2_expected_games, tennis_get_score_table_games(PLAYER2, 3));
}

TEST(tennis, Save_games_to_score_table_after_set_win)
{
    uint8_t player1_expected_games = 5;
    uint8_t player2_expected_games = 7;

    games_win(PLAYER1, 5);
    games_win(PLAYER2, 5);
    games_win(PLAYER2, 1);
    games_win(PLAYER2, 1);

    TEST_ASSERT_EQUAL(player1_expected_games, tennis_get_score_table_games(PLAYER1, 1));
    TEST_ASSERT_EQUAL(player2_expected_games, tennis_get_score_table_games(PLAYER2, 1));
}

TEST(tennis, Save_games_to_score_table_after_second_set_win)
{
    uint8_t player1_expected_games_set1 = 5;
    uint8_t player2_expected_games_set1 = 7;

    games_win(PLAYER1, 5);
    games_win(PLAYER2, 5);
    games_win(PLAYER2, 1);
    games_win(PLAYER2, 1);

    uint8_t player1_expected_games_set2 = 6;
    uint8_t player2_expected_games_set2 = 3;

    games_win(PLAYER2, 2);
    games_win(PLAYER1, 5);
    games_win(PLAYER2, 1);
    games_win(PLAYER1, 1);

    TEST_ASSERT_EQUAL(player1_expected_games_set1, tennis_get_score_table_games(PLAYER1, 1));
    TEST_ASSERT_EQUAL(player2_expected_games_set1, tennis_get_score_table_games(PLAYER2, 1));
    TEST_ASSERT_EQUAL(player1_expected_games_set2, tennis_get_score_table_games(PLAYER1, 2));
    TEST_ASSERT_EQUAL(player2_expected_games_set2, tennis_get_score_table_games(PLAYER2, 2));
}

TEST(tennis, Save_games_to_score_table_after_third_set_win)
{
    uint8_t player1_expected_games = 6;
    uint8_t player2_expected_games = 1;

    set_win(PLAYER1);
    set_win(PLAYER2);

    games_win(PLAYER2, 1);
    games_win(PLAYER1, 6);

    TEST_ASSERT_EQUAL(player1_expected_games, tennis_get_score_table_games(PLAYER1, 3));
    TEST_ASSERT_EQUAL(player2_expected_games, tennis_get_score_table_games(PLAYER2, 3));
}

TEST(tennis, Save_games_to_score_table_after_win_in_tie_break)
{
    tie_break();
    uint8_t player1_expected_games = points_win_during_tie_break(PLAYER1, 7);

    TEST_ASSERT_EQUAL(player1_expected_games, tennis_get_score_table_games(PLAYER1, 1));
}

TEST(tennis, Player1_wins_state_match_ended)
{
    set_win(PLAYER1);
    set_win(PLAYER1);

    TEST_ASSERT_EQUAL(MATCH_ENDED, tennis_get_state());
}

TEST(tennis, Player2_wins_state_match_ended)
{
    set_win(PLAYER2);
    set_win(PLAYER2);

    TEST_ASSERT_EQUAL(MATCH_ENDED, tennis_get_state());
}

TEST(tennis, Match_ended_no_more_points_for_players)
{
    uint8_t expected_points = 0;

    set_win(PLAYER2);
    set_win(PLAYER2);

    tennis_point(PLAYER2);
    tennis_point(PLAYER1);

    TEST_ASSERT_EQUAL(expected_points, tennis_get_points(PLAYER1));
    TEST_ASSERT_EQUAL(expected_points, tennis_get_points(PLAYER2));
}

TEST(tennis, Player1_wins_winner_is_PLAYER1)
{
    set_win(PLAYER1);
    set_win(PLAYER1);

    TEST_ASSERT_EQUAL(PLAYER1, tennis_winner_get());
}

TEST(tennis, Player2_wins_winner_is_PLAYER2)
{
    set_win(PLAYER2);
    set_win(PLAYER1);
    set_win(PLAYER2);

    TEST_ASSERT_EQUAL(PLAYER2, tennis_winner_get());
}

TEST (tennis, Player1_is_player_to_serve_after_init)
{
    enum player player_to_serve = PLAYER1;
    TEST_ASSERT_EQUAL(player_to_serve, tennis_get_player_to_serve());
}

TEST (tennis, Player2_is_player_to_serve_after_first_game)
{
    enum player player_to_serve = PLAYER2;

    game_win(PLAYER1);

    TEST_ASSERT_EQUAL(player_to_serve, tennis_get_player_to_serve());
}

TEST (tennis, Player1_is_player_to_serve_after_second_game)
{
    enum player player_to_serve = PLAYER1;

    games_win(PLAYER1, 2);
    
    TEST_ASSERT_EQUAL(player_to_serve, tennis_get_player_to_serve());
}

TEST (tennis, Player_NONE_is_player_to_serve_after_end_of_match)
{
    set_win(PLAYER1);
    set_win(PLAYER1);

    enum player player_to_serve = PLAYER_NONE;

    TEST_ASSERT_EQUAL(player_to_serve, tennis_get_player_to_serve());
}

TEST(tennis, EVENT_NONE_after_init)
{
    TEST_ASSERT_EQUAL(EVENT_NONE, tennis_get_event());
}

TEST(tennis, MATCH_POINT_event)
{
    set_win(PLAYER1);
    games_win(PLAYER1, 5);

    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);

    TEST_ASSERT_EQUAL(MATCH_POINT, tennis_get_event());
}

TEST(tennis, MATCH_POINT_40_0_and_opposte_player_gets_point)
{
    set_win(PLAYER1);
    games_win(PLAYER1, 5);

    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER2);

    TEST_ASSERT_EQUAL(MATCH_POINT, tennis_get_event());
}

TEST(tennis, MATCH_POINT_40_30_and_opposte_player_gets_point)
{
    set_win(PLAYER1);
    games_win(PLAYER1, 5);

    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);

    TEST_ASSERT_EQUAL(EVENT_NONE, tennis_get_event());
}

TEST(tennis, MATCH_POINT_during_tie_break_5_5_and_player_gets_point)
{
    tie_break();
    points_win_during_tie_break(PLAYER1, 5);
    points_win_during_tie_break(PLAYER2, 5);
    points_win_during_tie_break(PLAYER1, 1);

    TEST_ASSERT_EQUAL(MATCH_POINT, tennis_get_event());
}