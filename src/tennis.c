#include <string.h>
#include "tennis.h"

typedef struct
{
  uint8_t points;
  uint8_t games;
  uint8_t sets;
  bool is_advantage;
} player_t;

static player_t player1;
static player_t player2;

static enum player winner;
static enum player player_to_serve;

static game_state_t state;
static event_t event;

static uint8_t score_table[PLAYERS][MAX_SETS_NO];

static void tennis_point_handle(player_t *player);
static player_t *tennis_get_opposite_player(player_t *player);
static void tennis_add_15_points(player_t *player);
static void tennis_add_10_points(player_t *player);
static void tennis_40_points_handle(player_t *player);
static uint8_t tennis_get_player_points(player_t *player);
static bool tennis_is_player_advantage(player_t *player);
static void tennis_set_advantage(player_t *player);
static void tennis_reset_advantage(player_t *player);
static void tennis_reset_points(void);
static void tennis_add_game(player_t *player);
static void tennis_add_set(player_t *player);
static uint8_t tennis_get_player_games(player_t *player);
static void tennis_game_win_handle(player_t *player);
static void tennis_set_win_check(player_t *player);
static void tennis_add_1_point(player_t *player);
static void tennis_set_win_handle(player_t *player);
static void tennis_reset_games(void);
static void tennis_regular_point_handle(player_t *player);
static void tennis_tie_break_point_handle(player_t *player);
static void tennis_score_table_save(void);
static void tennis_match_win_check(player_t *player);
static void tennis_change_player_to_serve(void);
static void tennis_event_check(void);
static bool tennis_match_point_for_player_check(player_t *player);
static bool tennis_set_point_for_player_check(player_t *player);
static bool tennis_is_games_result_for_possible_set_point(player_t *player);
static bool tennis_is_points_result_for_possible_set_point(player_t *player);

void tennis_init(void)
{
    player1.points = 0;
    player1.games = 0;
    player1.sets = 0;
    player1.is_advantage = false;

    player2.points = 0;
    player2.games = 0;
    player2.sets = 0;
    player2.is_advantage = false;

    winner = PLAYER_NONE;
    player_to_serve = PLAYER1;
    state = REGULAR;
    event = EVENT_NONE;
    memset(score_table, 0, 6 * sizeof(uint8_t));
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
    if(REGULAR == state)
    {
        tennis_regular_point_handle(player);
    }
    else if(TIE_BREAK == state)
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

static void tennis_tie_break_point_handle(player_t *player)
{
    player_t *opposite_player = tennis_get_opposite_player(player);

    if(player->points < 6)
    {
        tennis_add_1_point(player);
    }
    else if(player->points == 6 && opposite_player->points < 6)
    {
        tennis_add_game(player);
        tennis_set_win_handle(player);
    }
    else if(player->points == opposite_player->points && player->is_advantage == false && opposite_player->is_advantage == false)
    {
        tennis_set_advantage(player);
    }
    else if(true == player->is_advantage)
    {
        tennis_reset_advantage(player);
        tennis_add_game(player);
        tennis_set_win_handle(player);
    }
    else if(true == opposite_player->is_advantage)
    {
        tennis_reset_advantage(opposite_player);
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
        else if(false == tennis_is_player_advantage(player))
        {
            tennis_set_advantage(player);
        }
        else if(true == tennis_is_player_advantage(player))
        {
            tennis_reset_advantage(player);
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
    tennis_reset_points();
    tennis_add_game(player);
    tennis_change_player_to_serve();
    tennis_set_win_check(player);
}

static void tennis_set_win_handle(player_t *player)
{
    tennis_add_set(player);
    tennis_score_table_save();
    tennis_reset_points();
    tennis_reset_games();
    tennis_match_win_check(player);
}

static void tennis_set_win_check(player_t *player)
{
    player_t *opposite_player = tennis_get_opposite_player(player);

    if(((6 == tennis_get_player_games(player)) && 5 > (tennis_get_player_games(opposite_player))) || 
       ((7 == tennis_get_player_games(player)) && (5 == tennis_get_player_games(opposite_player))))
    {
        tennis_set_win_handle(player);
    }
    else if(6 == tennis_get_player_games(player) && 6 == tennis_get_player_games(opposite_player))
    {
        state = TIE_BREAK;
    }
}

static void tennis_reset_games(void)
{
    player1.games = 0;
    player2.games = 0;
}

static void tennis_add_1_point(player_t *player)
{
    player->points++;
}

static uint8_t tennis_get_player_games(player_t *player)
{
    return player->games;
}

static void tennis_add_set(player_t *player)
{
    player->sets++;
}

static void tennis_add_game(player_t *player)
{
    player->games++;
}

static void tennis_reset_points(void)
{
    player1.points = 0;
    player2.points = 0;
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

    return &player1;
}

uint8_t tennis_get_points(enum player player)
{
    if(player == PLAYER1)
    {
        return player1.points;
    }

    return player2.points;
}

uint8_t tennis_get_games(enum player player)
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

uint8_t tennis_get_sets(enum player player)
{
    if(player == PLAYER1)
    {
        return player1.sets;
    }

    return player2.sets;
}

game_state_t tennis_get_state(void)
{
    return state;
}

uint8_t tennis_get_score_table_games(enum player player, uint8_t set)
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
        state = MATCH_ENDED;
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
        state = REGULAR;
    }
}

enum player tennis_winner_get(void)
{
    return winner;
}

uint8_t tennis_get_current_set(void)
{
    return player1.sets + player2.sets + 1;
}

enum player tennis_get_player_to_serve(void)
{
    return player_to_serve;
}

static void tennis_change_player_to_serve(void)
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

event_t tennis_get_event(void)
{
    return event;
}

static void tennis_event_check(void)
{
    if(true == tennis_set_point_for_player_check(&player1))
    {
        if(true == tennis_match_point_for_player_check(&player1))
        {
            event = MATCH_POINT;
        }
        else
        {
            event = SET_POINT;
        }
    }
    else if(true == tennis_set_point_for_player_check(&player2))
    {
        if(true == tennis_match_point_for_player_check(&player2))
        {
            event = MATCH_POINT;
        }
        else
        {
            event = SET_POINT;
        }
    }
    else
    {
        event = EVENT_NONE;
    }
}

static bool tennis_match_point_for_player_check(player_t *player)
{
    if((SETS_TO_WIN_MATCH - 1) == player->sets)
    {
        return true;
    }

    return false;
}

static bool tennis_set_point_for_player_check(player_t *player)
{
    if(true == tennis_is_games_result_for_possible_set_point(player) && true == tennis_is_points_result_for_possible_set_point(player))
    {
        return true;
    }

    return false;
}

static bool tennis_is_games_result_for_possible_set_point(player_t *player)
{
    player_t *opposite_player = tennis_get_opposite_player(player);

    return (((player->games == (GAMES_TO_WIN_SET - 1)) && (opposite_player->games < (GAMES_TO_WIN_SET - 1))) || ((player->games == GAMES_TO_WIN_SET) && (opposite_player->games >= (GAMES_TO_WIN_SET - 1))));
}

static bool tennis_is_points_result_for_possible_set_point(player_t *player)
{
    player_t *opposite_player = tennis_get_opposite_player(player);

    switch(state)
    {
        case REGULAR:
            return ((40 == player->points && 40 > opposite_player->points) || (true == tennis_is_player_advantage(player)));
            break;

        case TIE_BREAK:
            return ((6 == player->points && 6 > opposite_player->points) || (true == tennis_is_player_advantage(player)));
            break;
        
        case MATCH_ENDED:
            //FALLTHOUGH
            break;
    }

    return false;
}