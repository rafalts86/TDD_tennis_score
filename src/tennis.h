#include <stdint.h>

enum player
{
    PLAYER1,
    PLAYER2,
};

uint8_t tennis_get_points(enum player player);
void tennis_point(enum player player);