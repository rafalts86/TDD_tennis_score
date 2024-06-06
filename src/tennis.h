#include <stdint.h>
#include <stdbool.h>

#define PLAYERS                 2
#define MAX_SETS_NO             5

#define SETS_TO_WIN_MATCH       2       //women
//#define SETS_TO_WIN_MATCH     3       //men

typedef enum
{
    REGULAR,
    TIE_BREAK,
    MATCH_ENDED
} game_state_t;

enum player
{
    PLAYER_NONE = -1,
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
enum player tennis_winner_get(void);
uint8_t tennis_get_current_set(void);