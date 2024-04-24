#include <stdint.h>
#include <stdbool.h>

enum player
{
    PLAYER1,
    PLAYER2,
};

void tennis_init(void);
void tennis_point(enum player player);
uint8_t tennis_get_points(enum player player);
uint8_t tennis_get_gems(enum player player);
bool tennis_is_advantage(enum player player);