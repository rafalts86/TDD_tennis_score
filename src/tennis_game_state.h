#pragma once


typedef enum
{
    REGULAR,
    TIE_BREAK,
    MATCH_ENDED
} game_state_t;


void tennis_game_state_init(void);
game_state_t tennis_game_state_get(void);
void tennis_game_state_set(game_state_t new_state);