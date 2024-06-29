#include <string.h>
#include "tennis.h"

static player_t player1;
static player_t player2;

static enum player winner;
static enum player player_to_serve;

static uint8_t score_table[PLAYERS][MAX_SETS_NO];


static void tennis_point_handle(player_t *player);
static void tennis_regular_point_handle(player_t *player);
static void tennis_tie_break_point_handle(player_t *player);

static void tennis_15_points_add(player_t *player);
static void tennis_10_points_add(player_t *player);
static void tennis_40_points_handle(player_t *player);
static void tennis_1_point_add(player_t *player);

static uint8_t tennis_player_points_get(player_t *player);
static uint8_t tennis_player_games_get(player_t *player);

static void tennis_advantage_set(player_t *player);
static void tennis_advantage_reset(player_t *player);

static void tennis_points_reset(void);
static void tennis_games_reset(void);
static void tennis_sets_reset(void);
static void tennis_advantages_reset(void);

static void tennis_game_add(player_t *player);
static void tennis_set_add(player_t *player);

static void tennis_set_win_check(player_t *player);
static void tennis_match_win_check(player_t *player);

static void tennis_game_win_handle(player_t *player);
static void tennis_set_win_handle(player_t *player);

static void tennis_score_table_save(void);
static void tennis_score_table_reset(void);

static void tennis_player_to_serve_change(void);
static void tennis_player_to_serve_set(enum player player);

static void tennis_winner_set(enum player player);



void tennis_init(void)
{
    tennis_points_reset();
    tennis_games_reset();
    tennis_sets_reset();
    tennis_advantages_reset();
    tennis_winner_set(PLAYER_NONE);
    tennis_player_to_serve_set(PLAYER1);
    tennis_game_state_init();
    tennis_event_init();
    tennis_score_table_reset();
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
    if(REGULAR == tennis_game_state_get())
    {
        tennis_regular_point_handle(player);
    }
    else if(TIE_BREAK == tennis_game_state_get())
    {
        tennis_tie_break_point_handle(player);
    }

    tennis_event_check();
}

static void tennis_regular_point_handle(player_t *player)
{
    switch(player->points)
    {
        case 0:
        case 15:
            tennis_15_points_add(player);
            break;
        
        case 30:
            tennis_10_points_add(player);
            break;

        case 40:
            tennis_40_points_handle(player);
            break;
    }
}

static void tennis_tie_break_point_handle(player_t *player)
{
    player_t *opposite_player = tennis_opposite_player_get(player);

    if(player->points < 6)
    {
        tennis_1_point_add(player);
    }
    else if(player->points == 6 && opposite_player->points < 6)
    {
        tennis_game_add(player);
        tennis_set_win_handle(player);
    }
    else if(player->points == opposite_player->points && player->is_advantage == false && opposite_player->is_advantage == false)
    {
        tennis_advantage_set(player);
    }
    else if(true == player->is_advantage)
    {
        tennis_advantage_reset(player);
        tennis_game_add(player);
        tennis_set_win_handle(player);
    }
    else if(true == opposite_player->is_advantage)
    {
        tennis_advantage_reset(opposite_player);
    }
}

static void tennis_40_points_handle(player_t *player)
{
    player_t *opposite_player = tennis_opposite_player_get(player);

    if(40 == tennis_player_points_get(opposite_player))
    {
        if(true == tennis_is_player_advantage(opposite_player))
        {
           tennis_advantage_reset(opposite_player);
        }
        else if(false == tennis_is_player_advantage(player))
        {
            tennis_advantage_set(player);
        }
        else if(true == tennis_is_player_advantage(player))
        {
            tennis_advantage_reset(player);
            tennis_game_win_handle(player);
        }
    }
    else
    {
       tennis_game_win_handle(player);
    }
}

static void tennis_game_win_handle(player_t *player)
{
    tennis_points_reset();
    tennis_game_add(player);
    tennis_player_to_serve_change();
    tennis_set_win_check(player);
}

static void tennis_set_win_handle(player_t *player)
{
    tennis_set_add(player);
    tennis_score_table_save();
    tennis_points_reset();
    tennis_games_reset();
    tennis_match_win_check(player);
}

static void tennis_set_win_check(player_t *player)
{
    player_t *opposite_player = tennis_opposite_player_get(player);

    if(((6 == tennis_player_games_get(player)) && 5 > (tennis_player_games_get(opposite_player))) || 
       ((7 == tennis_player_games_get(player)) && (5 == tennis_player_games_get(opposite_player))))
    {
        tennis_set_win_handle(player);
    }
    else if(6 == tennis_player_games_get(player) && 6 == tennis_player_games_get(opposite_player))
    {
        tennis_game_state_set(TIE_BREAK);
    }
}

static void tennis_games_reset(void)
{
    player1.games = 0;
    player2.games = 0;
}

static void tennis_1_point_add(player_t *player)
{
    player->points++;
}

static uint8_t tennis_player_games_get(player_t *player)
{
    return player->games;
}

static void tennis_set_add(player_t *player)
{
    player->sets++;
}

static void tennis_game_add(player_t *player)
{
    player->games++;
}

static void tennis_points_reset(void)
{
    player1.points = 0;
    player2.points = 0;
}

static void tennis_advantage_set(player_t *player)
{
    player->is_advantage = true;
}

static void tennis_advantage_reset(player_t *player)
{
    player->is_advantage = false;
}

bool tennis_is_player_advantage(player_t *player)
{
    return player->is_advantage;
}

static uint8_t tennis_player_points_get(player_t *player)
{
    return player->points;
}

static void tennis_15_points_add(player_t *player)
{
    player->points += 15;
}

static void tennis_10_points_add(player_t *player)
{
    player->points += 10;
}

player_t *tennis_opposite_player_get(player_t *player)
{
    if(player == &player1)
    {
        return &player2;
    }

    return &player1;
}

uint8_t tennis_points_get(enum player player)
{
    if(player == PLAYER1)
    {
        return player1.points;
    }

    return player2.points;
}

uint8_t tennis_games_get(enum player player)
{
    if(player == PLAYER1)
    {
        return player1.games;
    }

    return player2.games;
}

bool tennis_is_advantage(enum player player)
{
    if(player == PLAYER1)
    {
        return player1.is_advantage;
    }

    return player2.is_advantage;
}

uint8_t tennis_sets_get(enum player player)
{
    if(player == PLAYER1)
    {
        return player1.sets;
    }

    return player2.sets;
}

uint8_t tennis_score_table_games_get(enum player player, uint8_t set)
{
    return score_table[player][set-1];
}

static void tennis_score_table_save(void)
{
    uint8_t set_no = player1.sets + player2.sets;

    score_table[PLAYER1][set_no - 1] = player1.games;
    score_table[PLAYER2][set_no - 1] = player2.games;
}

static void tennis_match_win_check(player_t *player)
{
    if(SETS_TO_WIN_MATCH == player->sets)
    {
        tennis_game_state_set(MATCH_ENDED);
        player_to_serve = PLAYER_NONE;

        if(player == &player1)
        {
            winner = PLAYER1;
        }
        else 
        {
            winner = PLAYER2;
        }
    }
    else
    {
        tennis_game_state_set(REGULAR);
    }
}

enum player tennis_winner_get(void)
{
    return winner;
}

uint8_t tennis_current_set_get(void)
{
    return player1.sets + player2.sets + 1;
}

enum player tennis_player_to_serve_get(void)
{
    return player_to_serve;
}

static void tennis_player_to_serve_change(void)
{
    if(PLAYER1 == player_to_serve)
    {
        player_to_serve = PLAYER2;
    }
    else
    {
        player_to_serve = PLAYER1;
    }
}

player_t *tennis_player_get(enum player selected_player)
{
    if(PLAYER1 == selected_player)
    {
        return &player1;
    }

    return &player2;
}

static void tennis_sets_reset(void)
{
    player1.sets = 0;
    player2.sets = 0;
}

static void tennis_advantages_reset(void)
{
    player1.is_advantage = false;
    player2.is_advantage = false;
}

static void tennis_winner_set(enum player player)
{
    winner = player;
}

static void tennis_player_to_serve_set(enum player player)
{
    player_to_serve = player;
}

static void tennis_score_table_reset(void)
{
    memset(score_table, 0, 6 * sizeof(uint8_t));
}