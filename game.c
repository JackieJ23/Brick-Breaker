#include "system.h"
#include "ledmat.h"
#include "display.h"
#include "pacer.h"
#include "pio.h"
#include "pacer.h"
#include "navswitch.h"
#include "ball.h"
#include "player.h"
#include <stdbool.h>
#include <stdint.h>

#define PACER_RATE 1000 //Hz


// Most of the contents can be moved to its own "gamelogic.c" file.
#define PLAYER_UPDATE_RATE 50
#define PLAYER_COUNTER_TOTAL PACER_RATE/PLAYER_UPDATE_RATE

// Bitmap of whole game.
/*  Bitmap can be used to identify position of player, position of bricks
    and easily use bit-aritmetic for game logic. */
static uint8_t gameMap[LEDMAT_COLS_NUM] =
{
    0x00, 0x00, 0x00, 0x00, 0x00
};

/** Updates the players position and changes the positon on the screen
    @param player Pointer to the player to update. */
void update_player(Player_t* player)
{

    display_pixel_set(player->pLeft, player->pRow, false);
    display_pixel_set(player->pRight, player->pRow, false);
    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        move_player_right(player);
    }

    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        move_player_left(player);
    }

    // Updates the position of the player on the gameMap (bitmap).
    // Note: not needed if the player pos is updated using display_pixel_set().
    for (uint8_t i = 0; i < LEDMAT_COLS_NUM; i++) {
        if (i == player->pLeft || i == player->pRight) {
            gameMap[i] |= (1 << (player->pRow));
        } else {
            gameMap[i] &= ~(1 << (player->pRow));
        }
    }
    display_pixel_set(player->pLeft, player->pRow, true);
    display_pixel_set(player->pRight, player->pRow, true);
}

/** Updates the display of the whole game by iterating through the gameMap and
    changing the values on the display.c module's own bitmap to be displayed
    could be slow.
    Note: Not needed if directly updating display.c module's bitmap in ball and
    player refersh/update code.
*/
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

// Temp stuff for updating ball on screen
#define BALL_UPDATE_RATE 50
#define BALL_COUNTER_TOTAL PACER_RATE/BALL_UPDATE_RATE

/** Updates the balls position and moves the ball on the screen
    @param ball pointer to the ball to move */
void refresh_ball(Ball_t* ball)
{
    // gameMap[ball->colPos] &= ~(1 << ball->rowPos);
    display_pixel_set(ball->colPos, ball->rowPos, false);
    update_ball_pos(ball);
    display_pixel_set(ball->colPos, ball->rowPos, true);
    // gameMap[ball->colPos] |= (1 << ball->rowPos);
}

int main(void)
{
    //~ uint8_t current_column = 0;

    // Initilise system
    system_init();
    pacer_init(500);
    navswitch_init();
    display_init();


    // Create new ball
    Ball_t gameBall = new_ball(0, 0, 1, 1);
    Player_t player = player_init(2, 6);

    uint64_t playerUpdateCounter = 0;
    uint64_t ballUpdateCounter = 0;
    uint64_t DisplayUpdateCounter = 0;



    while(true)
    {
        pacer_wait();

        if (playerUpdateCounter >= PLAYER_COUNTER_TOTAL) {
            navswitch_update();
            update_player(&player);
            playerUpdateCounter = 0;
        }
        playerUpdateCounter++;

        if (playerUpdateCounter >= BALL_COUNTER_TOTAL) {
            refresh_ball(&gameBall);
            ballUpdateCounter = 0;
        }
        ballUpdateCounter++;

        if (DisplayUpdateCounter >= 500) {
            display_update();
        }
        DisplayUpdateCounter++;
    }
}
