#include "tennis.h"

static uint8_t player1_points;
static uint8_t player2_points;


void tennis_init(void)
{
    player1_points = 0;
    player2_points = 0;
}

void tennis_point(enum player player)
{
    if(player == PLAYER1)
    {
        if(player1_points < 30)
        {
            player1_points += 15;
        }
        else if(player1_points == 30)
        {
            player1_points += 10;
        }
    }
    else if(player == PLAYER2)
    {
        if(player2_points < 30)
        {
            player2_points += 15;
        }
        else if(player2_points == 30)
        {
            player2_points += 10;
        }
    }
}

uint8_t tennis_get_points(enum player player)
{
    if(player == PLAYER1)
    {
        return player1_points;
    }
    else if(player == PLAYER2)
    {
        return player2_points;
    }
}