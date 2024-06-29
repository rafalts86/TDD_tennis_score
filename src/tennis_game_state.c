#include "tennis_game_state.h"

static game_state_t state;


void tennis_game_state_init(void)
{
    state = REGULAR;
}

game_state_t tennis_game_state_get(void)
{
    return state;
}

void tennis_game_state_set(game_state_t new_state)
{
    state = new_state;
}