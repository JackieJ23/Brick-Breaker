/** @file   gamelogic.c
    @author Jackie Jone, James Hazelhurst
    @date   17 October 2021
    @brief Game logic for Brick Breaker
*/
#include "system.h"
#include "display.h"
#include "navswitch.h"
#include "ball.h"
#include "player.h"
#include <stdbool.h>
#include <stdint.h>

// Bitmap of whole game.
/*  Bitmap can be used to identify position of player, position of bricks
    and easily use bit-aritmetic for game logic. */
// static uint8_t gameMap[LEDMAT_COLS_NUM] =
// {
//     0x00, 0x00, 0x00, 0x00, 0x00
// };

/** Updates the players position and changes the positon on the screen */
void update_player(void)
{
    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        move_player_right();
    }

    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        move_player_left();
    }

    // Updates the position of the player on the gameMap (bitmap).
    // Note: not needed if the player pos is updated using display_pixel_set().
    // for (uint8_t i = 0; i < LEDMAT_COLS_NUM; i++) {
    //     if (i == player->pLeft || i == player->pRight) {
    //         gameMap[i] |= (1 << (player->pRow));
    //     } else {
    //         gameMap[i] &= ~(1 << (player->pRow));
    //     }
    // }
}

// No longer needed
/** Updates the display of the whole game by iterating through the gameMap and
    changing the values on the display.c module's own bitmap to be displayed
    could be slow.
    Note: Not needed if directly updating display.c module's bitmap in ball and
    player refersh/update code. */
// void game_update_display()
// {
//     bool pixelOn;
//     for (uint8_t col = 0; col < LEDMAT_COLS_NUM; col++) {
//         for (uint8_t row = 0; row < LEDMAT_ROWS_NUM; row++) {
//             pixelOn = ((gameMap[col] >> row) & 1);
//             display_pixel_set(col, row, pixelOn);
//         }
//     }

//     display_update();
// }

void refresh_ball(void)
{
    Ball_vect_t ballPos = get_ball_position();
    Ball_vect_t futureBallPos = get_future_ball_position();
    Player_t playerPos = get_player_position();

    if (ballPos.y >= LEDMAT_ROWS_NUM - 1) {
        ; // TODO: End game here
    }

    // Ball is in the row above the player.
    if (ballPos.y == playerPos.pRow - 1 && futureBallPos.y > ballPos.y) {

        // Ball is above left pixel of player.
        if (ballPos.x == playerPos.pLeft) {
            // flip_vert_ball_dir();
            change_ball_dir(-1, -1);

        // Ball is above right pixek of player.
        } else if (ballPos.x == playerPos.pRight) {
            change_ball_dir(-1, 1);

        // Ball is coming towards the left player pixel from the top left corner
        } else if (futureBallPos.x == playerPos.pLeft) {
            change_ball_dir(-1, -1);

        // Ball is coming towards the right player pixel from the top right corner
        } else if (futureBallPos.x == playerPos.pRight) {
            change_ball_dir(-1, 1);
        }
    }
    update_ball_pos();
}
