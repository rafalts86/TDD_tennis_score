#include <stdbool.h>
#include "tennis_event.h"
#include "tennis.h"

static event_t event;

static bool tennis_match_point_for_player_check(player_t *player);
static bool tennis_set_point_for_player_check(player_t *player);
static bool tennis_is_games_result_for_possible_set_point(player_t *player);
static bool tennis_is_points_result_for_possible_set_point(player_t *player);


void tennis_event_init(void)
{
    event = EVENT_NONE;
}

event_t tennis_event_get(void)
{
    return event;
}

void tennis_event_set(event_t new_event)
{
    event = new_event;
}

void tennis_event_check(void)
{
    player_t *player1 = tennis_player_get(PLAYER1);
    player_t *player2 = tennis_player_get(PLAYER2);

    if(true == tennis_set_point_for_player_check(player1))
    {
        if(true == tennis_match_point_for_player_check(player1))
        {
            tennis_event_set(MATCH_POINT);
        }
        else
        {
            tennis_event_set(SET_POINT);
        }
    }
    else if(true == tennis_set_point_for_player_check(player2))
    {
        if(true == tennis_match_point_for_player_check(player2))
        {
            tennis_event_set(MATCH_POINT);
        }
        else
        {
            tennis_event_set(SET_POINT);
        }
    }
    else
    {
        tennis_event_set(EVENT_NONE);
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

    switch(tennis_get_state())
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