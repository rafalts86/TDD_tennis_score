#include "unity/fixture/unity_fixture.h"

#include "tennis.h"

uint8_t gem_win(enum player player)
{
    for(uint8_t i = 0; i < 4; i++)
    {
        tennis_point(player);
    }

    return 1;
}

uint8_t gems_win(enum player player, uint8_t no_gems)
{
    for(uint8_t i = 0; i < no_gems; i++)
    {
        gem_win(player);
    }

    return 1;
}

uint8_t set_win(enum player player)
{
    for(uint8_t i = 0; i < 6; i++)
    {
        gem_win(player);
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
    gems_win(PLAYER1, 5);
    gems_win(PLAYER2, 5);
    gem_win(PLAYER2);
    gem_win(PLAYER1);
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
    uint8_t expected_gems = 0;
    uint8_t expected_points = 0;

    expected_gems += gem_win(PLAYER1);

    TEST_ASSERT_EQUAL(expected_points, tennis_get_points(PLAYER1));
    TEST_ASSERT_EQUAL(expected_gems, tennis_get_gems(PLAYER1));
}

TEST(tennis, Player2_gets_four_points)
{
    uint8_t expected_gems = 0;
    uint8_t expected_points = 0;

    expected_gems += gem_win(PLAYER2);

    TEST_ASSERT_EQUAL(expected_points, tennis_get_points(PLAYER2));
    TEST_ASSERT_EQUAL(expected_gems, tennis_get_gems(PLAYER2));
}

TEST(tennis, Player1_gets_gem_Player2_reset_points)
{
    uint8_t expected_points = 0;
   
    tennis_point(PLAYER2);
    gem_win(PLAYER1);

    TEST_ASSERT_EQUAL(expected_points, tennis_get_points(PLAYER2));
}

TEST(tennis, Player2_gets_gem_Player1_reset_points)
{
    uint8_t expected_points = 0;

    tennis_point(PLAYER1);
    gem_win(PLAYER2);

    TEST_ASSERT_EQUAL(expected_points, tennis_get_points(PLAYER1));
}

TEST(tennis, Player1_advantage)
{
    advantage(PLAYER1);

    TEST_ASSERT_EQUAL(true, tennis_is_advantage(PLAYER1));
}

TEST(tennis, Player1_wins_after_advantage)
{
    uint8_t expectet_gems = 1;

    advantage(PLAYER1);
    tennis_point(PLAYER1);

    TEST_ASSERT_EQUAL(false, tennis_is_advantage(PLAYER1));
    TEST_ASSERT_EQUAL(expectet_gems, tennis_get_gems(PLAYER1));
}

TEST(tennis, Player1_advantage_and_player2_gets_point)
{
    uint8_t expectet_gems = 0;
    uint8_t expectet_points = 40;

    advantage(PLAYER1);
    tennis_point(PLAYER2);

    TEST_ASSERT_EQUAL(false, tennis_is_advantage(PLAYER1));
    TEST_ASSERT_EQUAL(expectet_gems, tennis_get_gems(PLAYER1));
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
    uint8_t expectet_gems = 1;

    advantage(PLAYER2);
    tennis_point(PLAYER2);

    TEST_ASSERT_EQUAL(false, tennis_is_advantage(PLAYER2));
    TEST_ASSERT_EQUAL(expectet_gems, tennis_get_gems(PLAYER2));
}

TEST(tennis, Player2_advantage_and_player1_gets_point)
{
    uint8_t expectet_gems = 0;
    uint8_t expectet_points = 40;

    advantage(PLAYER2);
    tennis_point(PLAYER1);

    TEST_ASSERT_EQUAL(false, tennis_is_advantage(PLAYER2));
    TEST_ASSERT_EQUAL(expectet_gems, tennis_get_gems(PLAYER2));
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

TEST(tennis, Player1_6gems_Player2_5gems_no_set_for_player1)
{
    uint8_t expected_sets = 0;

    gems_win(PLAYER1, 5);
    gems_win(PLAYER2, 5);
    gem_win(PLAYER1);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER1));
}

TEST(tennis, Player1_7gems_Player2_5gems_set_for_player1)
{
    uint8_t expected_sets = 1;

    gems_win(PLAYER1, 5);
    gems_win(PLAYER2, 5);
    
    gems_win(PLAYER1, 2);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER1));
}

TEST(tennis, Player1_6gems_Player2_6gems_tie_break)
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

TEST(tennis, Reset_gems_and_points_after_set_win)
{
    uint8_t expected_gems = 0;
    uint8_t expected_points = 0;
    uint8_t expected_sets = 1;

    gems_win(PLAYER1, 5);
    gems_win(PLAYER2, 5);

    gems_win(PLAYER1, 2);

    TEST_ASSERT_EQUAL(expected_sets, tennis_get_sets(PLAYER1));
    TEST_ASSERT_EQUAL(expected_gems, tennis_get_gems(PLAYER1));
    TEST_ASSERT_EQUAL(expected_gems, tennis_get_gems(PLAYER2));
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

TEST(tennis, Read_gems_from_score_table_after_init)
{
    uint8_t player1_expected_gems = 0;
    uint8_t player2_expected_gems = 0;

    TEST_ASSERT_EQUAL(player1_expected_gems, tennis_get_score_table_gems(PLAYER1, 1));
    TEST_ASSERT_EQUAL(player2_expected_gems, tennis_get_score_table_gems(PLAYER2, 1));
    TEST_ASSERT_EQUAL(player1_expected_gems, tennis_get_score_table_gems(PLAYER1, 2));
    TEST_ASSERT_EQUAL(player2_expected_gems, tennis_get_score_table_gems(PLAYER2, 2));
    TEST_ASSERT_EQUAL(player1_expected_gems, tennis_get_score_table_gems(PLAYER1, 3));
    TEST_ASSERT_EQUAL(player2_expected_gems, tennis_get_score_table_gems(PLAYER2, 3));
}

TEST(tennis, Save_gems_to_score_table_after_set_win)
{
    uint8_t player1_expected_gems = 5;
    uint8_t player2_expected_gems = 7;

    gems_win(PLAYER1, 5);
    gems_win(PLAYER2, 5);
    gems_win(PLAYER2, 1);
    gems_win(PLAYER2, 1);

    TEST_ASSERT_EQUAL(player1_expected_gems, tennis_get_score_table_gems(PLAYER1, 1));
    TEST_ASSERT_EQUAL(player2_expected_gems, tennis_get_score_table_gems(PLAYER2, 1));
}

TEST(tennis, Save_gems_to_score_table_after_second_set_win)
{
    uint8_t player1_expected_gems_set1 = 5;
    uint8_t player2_expected_gems_set1 = 7;

    gems_win(PLAYER1, 5);
    gems_win(PLAYER2, 5);
    gems_win(PLAYER2, 1);
    gems_win(PLAYER2, 1);

    uint8_t player1_expected_gems_set2 = 6;
    uint8_t player2_expected_gems_set2 = 3;

    gems_win(PLAYER2, 2);
    gems_win(PLAYER1, 5);
    gems_win(PLAYER2, 1);
    gems_win(PLAYER1, 1);

    TEST_ASSERT_EQUAL(player1_expected_gems_set1, tennis_get_score_table_gems(PLAYER1, 1));
    TEST_ASSERT_EQUAL(player2_expected_gems_set1, tennis_get_score_table_gems(PLAYER2, 1));
    TEST_ASSERT_EQUAL(player1_expected_gems_set2, tennis_get_score_table_gems(PLAYER1, 2));
    TEST_ASSERT_EQUAL(player2_expected_gems_set2, tennis_get_score_table_gems(PLAYER2, 2));
}

TEST(tennis, Save_gems_to_score_table_after_third_set_win)
{
    uint8_t player1_expected_gems = 6;
    uint8_t player2_expected_gems = 1;

    set_win(PLAYER1);
    set_win(PLAYER2);

    gems_win(PLAYER2, 1);
    gems_win(PLAYER1, 6);

    TEST_ASSERT_EQUAL(player1_expected_gems, tennis_get_score_table_gems(PLAYER1, 3));
    TEST_ASSERT_EQUAL(player2_expected_gems, tennis_get_score_table_gems(PLAYER2, 3));
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