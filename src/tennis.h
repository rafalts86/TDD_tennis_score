#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "tennis_event.h"
#include "tennis_game_state.h"

#define PLAYERS                 2
#define MAX_SETS_NO             5
#define GAMES_TO_WIN_SET        6

#define SETS_TO_WIN_MATCH       2       //women
//#define SETS_TO_WIN_MATCH     3       //men

typedef struct
{
  uint8_t points;
  uint8_t games;
  uint8_t sets;
  bool is_advantage;
} player_t;

enum player
{
    PLAYER_NONE = -1,
    PLAYER1,
    PLAYER2,
};


void tennis_init(void);
void tennis_point(enum player player);
uint8_t tennis_get_points(enum player player);
uint8_t tennis_get_games(enum player player);
uint8_t tennis_get_sets(enum player player);
bool tennis_is_advantage(enum player player);
bool tennis_is_player_advantage(player_t *player);
uint8_t tennis_get_score_table_games(enum player player, uint8_t set);
enum player tennis_winner_get(void);
uint8_t tennis_get_current_set(void);
enum player tennis_get_player_to_serve(void);
player_t *tennis_player_get(enum player selected_player);
player_t *tennis_get_opposite_player(player_t *player);