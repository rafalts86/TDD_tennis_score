#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    REGULAR,
    TIE_BREAK,
} game_state_t;

enum player
{
    PLAYER1,
    PLAYER2,
};

void tennis_init(void);
void tennis_point(enum player player);
uint8_t tennis_get_points(enum player player);
uint8_t tennis_get_gems(enum player player);
uint8_t tennis_get_sets(enum player player);
bool tennis_is_advantage(enum player player);
game_state_t tennis_get_state(void);
uint8_t tennis_get_score_table_gems(enum player player, uint8_t set);