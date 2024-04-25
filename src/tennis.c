#include "tennis.h"

typedef struct
{
  uint8_t points;
  uint8_t gems;
  uint8_t sets;
  bool is_advantage;
} player_t;

static player_t player1;
static player_t player2;

static void tennis_point_handle(player_t *player);
static player_t *tennis_get_opposite_player(player_t *player);
static void tennis_add_15_points(player_t *player);
static void tennis_add_10_points(player_t *player);
static void tennis_40_points_handle(player_t *player);
static uint8_t tennis_get_player_points(player_t *player);
static bool tennis_is_player_advantage(player_t *player);
static void tennis_set_advantage(player_t *player);
static void tennis_reset_advantage(player_t *player);

void tennis_init(void)
{
    player1.points = 0;
    player1.gems = 0;
    player1.sets = 0;
    player1.is_advantage = false;

    player2.points = 0;
    player2.gems = 0;
    player2.sets = 0;
    player2.is_advantage = false;
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
            tennis_add_15_points(player);
            break;
        
        case 30:
            tennis_add_10_points(player);
            break;

        case 40:
            tennis_40_points_handle(player);
            break;
    }
}

static void tennis_40_points_handle(player_t *player)
{
    player_t *opposite_player = tennis_get_opposite_player(player);

    if(40 == tennis_get_player_points(opposite_player))
    {
        if(true == tennis_is_player_advantage(opposite_player))
        {
           tennis_reset_advantage(opposite_player);
        }
        else if(false == player->is_advantage)
        {
            tennis_set_advantage(player);
        }
        else if(true == tennis_is_player_advantage(player))
        {
            player->points = 0;
            opposite_player->points = 0;
            player->is_advantage = false;
            player->gems++;
            if(6 == player->gems)
            {
                player->sets++;
            }
        }
    }
    else
    {
        player->points = 0;
        opposite_player->points = 0;
        player->gems++;
        if(6 == player->gems)
        {
            player->sets++;
        }
    }
}

static void tennis_set_advantage(player_t *player)
{
    player->is_advantage = true;
}

static void tennis_reset_advantage(player_t *player)
{
    player->is_advantage = false;
}

static bool tennis_is_player_advantage(player_t *player)
{
    return player->is_advantage;
}

static uint8_t tennis_get_player_points(player_t *player)
{
    return player->points;
}

static void tennis_add_15_points(player_t *player)
{
    player->points += 15;
}

static void tennis_add_10_points(player_t *player)
{
    player->points += 10;
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

uint8_t tennis_get_sets(enum player player)
{
    if(player == PLAYER1)
    {
        return player1.sets;
    }
    else if(player == PLAYER2)
    {
        return player2.sets;
    }
}