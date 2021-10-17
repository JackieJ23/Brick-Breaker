/** @file   player.h
    @author Jackie Jone, James Hazelhurst
    @date   17 October 2021
    @brief  2 Pixel player bar module
*/

#ifndef PLAYER_H
#define PLAYER_H
#include <stdint.h>

/** Structure defining position of player. */
typedef struct {
    uint8_t pLeft;
    uint8_t pRight;
    uint8_t pRow;
} Player_t;

/** Creates a new player with left of player on the given position
    @param colPos Horizontal (column) position to put the player. Left side on position.
    @param rowPos Veritcle (row) position to put the player.
    @return new player object. */
Player_t player_init(uint8_t colPos, uint8_t rowPos);


/** Moves a given player to the left by one pixel
    @param player Pointer a player to move. */
void move_player_left(Player_t* player);

/** Moves a given player to the right by one pixel
    @param player Pointer a player to move. */
void move_player_right(Player_t* player);

#endif
