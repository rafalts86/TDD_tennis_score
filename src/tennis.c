#include "tennis.h"

typedef struct
{
  uint8_t points;
  uint8_t gems;
  bool is_advantage;
} player_t;

static player_t player1;
static player_t player2;

static void tennis_point_handle(player_t *player);
static player_t *tennis_get_opposite_player(player_t *player);

void tennis_init(void)
{
    player1.points = 0;
    player1.gems = 0;
    player2.points = 0;
    player2.gems = 0;
    player1.is_advantage = false;
}

void tennis_point(enum player player)
{
    if(player == PLAYER1)
    {
        tennis_point_handle(&player1);
    }
    else if(player == PLAYER2)
    {
        tennis_point_handle(&player2);
    }
}

static void tennis_point_handle(player_t *player)
{
    switch(player->points)
    {
        case 0:
        case 15:
            player->points += 15;
            break;
        
        case 30:
            player->points += 10;
            break;

        case 40:
            player_t *opposite_player = tennis_get_opposite_player(player);

            if(40 == opposite_player->points)
            {
                player->is_advantage = true;
            }
            else
            {
                player->points = 0;
                opposite_player->points = 0;
                player->gems++;
            }
            break;
    }
}

static player_t *tennis_get_opposite_player(player_t *player)
{
    if(player == &player1)
    {
        return &player2;
    }
    else if(player == &player2)
    {
        return &player1;
    }
}

uint8_t tennis_get_points(enum player player)
{
    if(player == PLAYER1)
    {
        return player1.points;
    }
    else if(player == PLAYER2)
    {
        return player2.points;
    }
}

uint8_t tennis_get_gems(enum player player)
{
    if(player == PLAYER1)
    {
        return player1.gems;
    }
    else if(player == PLAYER2)
    {
        return player2.gems;
    }
}

bool tennis_is_advantage(enum player player)
{
    if(player == PLAYER1)
    {
        return player1.is_advantage;
    }
    else if(player == PLAYER2)
    {
        return player2.is_advantage;
    }
}