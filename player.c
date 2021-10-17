/** @file   player.c
    @author Jackie Jone, James Hazelhurst
    @date   17 October 2021
    @brief  2 Pixel player bar module
*/

#include <stdint.h>
#include "system.h"
#include "player.h"

#define PLAYER_WIDTH 2

/** Creates a new player with left of player on the given position
    @param colPos Horizontal (column) position to put the player. Left side on position.
    @param rowPos Veritcle (row) position to put the player.
    @return New player object. */
Player_t player_init(uint8_t colPos, uint8_t rowPos)
{
    // Make sure the player doesn't go off the screen horizontally
    if (colPos > LEDMAT_COLS_NUM - PLAYER_WIDTH) {
        colPos = LEDMAT_COLS_NUM - PLAYER_WIDTH;
    }

    // Make sure the player doesn't go off the screen vertically
    if (rowPos > LEDMAT_ROWS_NUM - 1) {
        rowPos = LEDMAT_ROWS_NUM - 1;
    }

    Player_t newPlayer =
    {
        .pLeft = colPos,
        .pRight = colPos + 1,
        .pRow = rowPos
    };

    return newPlayer;
}

/** Moves a given player to the left by one pixel
    @param player Pointer a player to move. */
void move_player_left(Player_t* player)
{
    if (player->pLeft > 0) {
        player->pRight--;
        player->pLeft--;
    }
}

/** Moves a given player to the right by one pixel
    @param player Pointer a player to move. */
void move_player_right(Player_t* player)
{
    if (player->pRight < LEDMAT_COLS_NUM - 1) {
        player->pRight++;
        player->pLeft++;
    }
}
