#include "unity/fixture/unity_fixture.h"

#include "tennis.h"

TEST_GROUP(tennis);

TEST_SETUP(tennis)
{
    /* Init before every test */
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

TEST(tennis, Player1_get_two_points)
{
    tennis_point(PLAYER1);
    tennis_point(PLAYER1);
    TEST_ASSERT_EQUAL(30, tennis_get_points(PLAYER1));
}