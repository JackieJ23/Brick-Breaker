/** @file   game.c
    @author Jackie Jone, James Hazelhurst
    @date   17 October 2021
    @brief  Brick Breaker game
*/

#include "system.h"
#include "ledmat.h"
#include "display.h"
#include "pacer.h"
#include "pio.h"
#include "pacer.h"
#include "navswitch.h"
#include "ball.h"
#include "player.h"
#include "gamelogic.h"
#include <stdbool.h>
#include <stdint.h>
#include "tinygl.h"
#include "../fonts/font3x5_1.h"

// Defining pacer and update rates.
#define PACER_RATE 500
#define PLAYER_UPDATE_RATE 50
#define DISPLAY_UPDATE_RATE 500
#define START_MENU_UPDATE_RATE 50

typedef enum {
    START_MENU,
    GAME_RUNNING,
    GAME_END
} Game_state_t;

static Game_state_t GAME_STATE = START_MENU;

void display_game_start(void)
{
    tinygl_init(500);
    tinygl_font_set(&font3x5_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text("GAME OVER");
}

int main(void)
{
    // Initilise system.
    system_init();
    pacer_init(PACER_RATE);
    navswitch_init();
    display_init();

    uint64_t ballSpeed = 3; // Change this to change ball speed.
    uint64_t BALL_COUNTER_TOTAL = PACER_RATE / ballSpeed;
    uint64_t PLAYER_COUNTER_TOTAL = PACER_RATE / PLAYER_UPDATE_RATE;
    uint64_t DISPLAY_COUNTER_TOTAL = PACER_RATE / DISPLAY_UPDATE_RATE;
    uint64_t START_MENU_COUNTER_TOTAL = PACER_RATE / START_MENU_UPDATE_RATE;
    uint64_t tickCounter = 0;

    bool newGame = true;
    display_game_start();

    while(true)
    {
        pacer_wait();

        switch (GAME_STATE) {
            default:
            case START_MENU:
                if (!newGame) {
                    display_clear();
                    display_update();
                    newGame = true;
                }

                if (tickCounter % START_MENU_COUNTER_TOTAL == 0) {
                    navswitch_update();
                    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                        GAME_STATE = GAME_RUNNING;
                    }
                }
                break;

            case GAME_RUNNING:
                if (newGame) {
                    // Could be added to a new game funciton
                    // Create new ball and initalise player
                    ball_init(2, 2, 1, 1);
                    player_init(2, 6);
                    newGame = false;
                }

                if (tickCounter % PLAYER_COUNTER_TOTAL == 0) {
                    navswitch_update();
                    update_player();
                }

                if (tickCounter % BALL_COUNTER_TOTAL == 0) {
                    if (ball_in_row(6)) {
                        GAME_STATE = GAME_END;
                    }
                    refresh_ball();
                }

                if (tickCounter % DISPLAY_COUNTER_TOTAL == 0) {
                    display_update();
                }
                break;
            case GAME_END:
                // display_update();
                // display_clear();
                // display_update();

                if (tickCounter % DISPLAY_COUNTER_TOTAL == 0) {
                    tinygl_update();
                }

                if (tickCounter % START_MENU_COUNTER_TOTAL == 0) {
                    navswitch_update();
                    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                        GAME_STATE = START_MENU;
                    }
                }
                break;
        }
        tickCounter++;
    }
}
