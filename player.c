/** @file   player.c
    @author Jackie Jone, James Hazelhurst
    @date   17 October 2021
    @brief  2 Pixel player bar module
*/

#include <stdint.h>
#include "system.h"
#include "player.h"
#include "display.h"

#define PLAYER_WIDTH 2

static Player_t player;

/** Creates a new player with left of player on the given position
    @param colPos Horizontal (column) position to put the player. Left side on position.
    @param rowPos Veritcle (row) position to put the player. */
void player_init(uint8_t colPos, uint8_t rowPos)
{
    // Make sure the player doesn't go off the screen horizontally
    if (colPos > LEDMAT_COLS_NUM - PLAYER_WIDTH) {
        colPos = LEDMAT_COLS_NUM - PLAYER_WIDTH;
    }

    // Make sure the player doesn't go off the screen vertically
    if (rowPos > LEDMAT_ROWS_NUM - 1) {
        rowPos = LEDMAT_ROWS_NUM - 1;
    }

    player.pLeft = colPos;
    player.pRight = colPos + 1;
    player.pRow = rowPos;

    display_pixel_set(player.pRight, player.pRow, true);
    display_pixel_set(player.pLeft, player.pRow, true);
}

/** Moves a given player to the left by one pixel. */
void move_player_left(void)
{
    if (player.pLeft > 0) {
        display_pixel_set(player.pLeft, player.pRow, false);
        display_pixel_set(player.pRight, player.pRow, false);

        player.pRight--;
        player.pLeft--;

        display_pixel_set(player.pRight, player.pRow, true);
        display_pixel_set(player.pLeft, player.pRow, true);
    }
}

/** Moves a given player to the right by one pixel. */
void move_player_right(void)
{
    if (player.pRight < LEDMAT_COLS_NUM - 1) {
        display_pixel_set(player.pLeft, player.pRow, false);
        display_pixel_set(player.pRight, player.pRow, false);

        player.pRight++;
        player.pLeft++;

        display_pixel_set(player.pRight, player.pRow, true);
        display_pixel_set(player.pLeft, player.pRow, true);
    }
}

/** Gets the position of the player
    @return playerCpy position of the player. */
Player_t get_player_position(void)
{
    Player_t playerCpy = {
        .pLeft = player.pLeft,
        .pRight = player.pRight,
        .pRow = player.pRow
    };
    return playerCpy;
}
