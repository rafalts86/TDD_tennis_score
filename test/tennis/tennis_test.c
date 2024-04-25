#include "unity/fixture/unity_fixture.h"

#include "tennis.h"

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
    tennis_point(PLAYER1);
    TEST_ASSERT_EQUAL(15, tennis_get_points(PLAYER1));
}

TEST(tennis, Player1_gets_two_points)
{
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    TEST_ASSERT_EQUAL(30, tennis_get_points(PLAYER1));
}

TEST(tennis, Player1_gets_three_points)
{
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    TEST_ASSERT_EQUAL(40, tennis_get_points(PLAYER1));
}

TEST(tennis, Player2_point)
{
    tennis_point(PLAYER2);
    TEST_ASSERT_EQUAL(15, tennis_get_points(PLAYER2));
}

TEST(tennis, Player2_gets_two_points)
{
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    TEST_ASSERT_EQUAL(30, tennis_get_points(PLAYER2));
}

TEST(tennis, Player2_gets_three_points)
{
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    TEST_ASSERT_EQUAL(40, tennis_get_points(PLAYER2));
}

TEST(tennis, Player1_gets_four_points)
{
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    TEST_ASSERT_EQUAL(0, tennis_get_points(PLAYER1));
    TEST_ASSERT_EQUAL(1, tennis_get_gems(PLAYER1));
}

TEST(tennis, Player2_gets_four_points)
{
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    TEST_ASSERT_EQUAL(0, tennis_get_points(PLAYER2));
    TEST_ASSERT_EQUAL(1, tennis_get_gems(PLAYER2));
}

TEST(tennis, Player1_gets_gem_Player2_reset_points)
{
    tennis_point(PLAYER1);
    tennis_point(PLAYER2);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    TEST_ASSERT_EQUAL(0, tennis_get_points(PLAYER2));
}

TEST(tennis, Player2_gets_gem_Player1_reset_points)
{
    tennis_point(PLAYER2);
    tennis_point(PLAYER1);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    TEST_ASSERT_EQUAL(0, tennis_get_points(PLAYER1));
}

TEST(tennis, Player1_advantage)
{
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);

    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);

    TEST_ASSERT_EQUAL(true, tennis_is_advantage(PLAYER1));
}

TEST(tennis, Player1_wins_after_advantage)
{
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);

    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);

    TEST_ASSERT_EQUAL(false, tennis_is_advantage(PLAYER1));
    TEST_ASSERT_EQUAL(1, tennis_get_gems(PLAYER1));
}

TEST(tennis, Player1_advantage_and_player2_gets_point)
{
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);

    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);

    tennis_point(PLAYER2);

    TEST_ASSERT_EQUAL(false, tennis_is_advantage(PLAYER1));
    TEST_ASSERT_EQUAL(0, tennis_get_gems(PLAYER1));
    TEST_ASSERT_EQUAL(40, tennis_get_points(PLAYER1));
    TEST_ASSERT_EQUAL(40, tennis_get_points(PLAYER2));
}

TEST(tennis, Player2_advantage)
{
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);

    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);

    TEST_ASSERT_EQUAL(true, tennis_is_advantage(PLAYER2));
}

TEST(tennis, Player2_wins_after_advantage)
{
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);

    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);

    TEST_ASSERT_EQUAL(false, tennis_is_advantage(PLAYER2));
    TEST_ASSERT_EQUAL(1, tennis_get_gems(PLAYER2));
}

TEST(tennis, Player2_advantage_and_player1_gets_point)
{
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);

    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);
    tennis_point(PLAYER2);

    tennis_point(PLAYER1);

    TEST_ASSERT_EQUAL(false, tennis_is_advantage(PLAYER2));
    TEST_ASSERT_EQUAL(0, tennis_get_gems(PLAYER2));
    TEST_ASSERT_EQUAL(40, tennis_get_points(PLAYER2));
    TEST_ASSERT_EQUAL(40, tennis_get_points(PLAYER1));
}