/** @file   game.c
    @author Jackie Jone, James Hazelhurst
    @date   17 October 2021
    @brief  Brick Breaker game
*/

#include "system.h"
#include "display.h"
#include "pacer.h"
#include "navswitch.h"
#include "ball.h"
#include "player.h"
#include "gamelogic.h"
#include <stdint.h>

// Defining pacer and update rates.
#define PACER_RATE 500
#define PLAYER_UPDATE_RATE 50
#define DISPLAY_UPDATE_RATE 500
#define START_MENU_UPDATE_RATE 500
#define BASE_BALL_SPEED 3


int main(void)
{
    // Initilise system.
    system_init();
    pacer_init(DISPLAY_TEXT_RATE);
    display_text_init(DISPLAY_TEXT_RATE);
    navswitch_init();
    display_init();

    // Update rate constants
    const uint64_t PLAYER_COUNTER_TOTAL = PACER_RATE / PLAYER_UPDATE_RATE;
    const uint64_t DISPLAY_COUNTER_TOTAL = PACER_RATE / DISPLAY_UPDATE_RATE;
    const uint64_t START_MENU_COUNTER_TOTAL = PACER_RATE / START_MENU_UPDATE_RATE;

    // Ball speed varibles
    uint64_t ballSpeed = BASE_BALL_SPEED;
    uint64_t BALL_COUNTER_TOTAL = PACER_RATE / ballSpeed;
    uint64_t ballSpeedIncrease;

    uint64_t tickCounter = 0;


    while(true)
    {
        pacer_wait();
        Game_state_t currentGameState = get_game_state();

        switch (currentGameState) {
            default:
            case START_MENU:
                if (tickCounter % START_MENU_COUNTER_TOTAL == 0) {
                    refresh_start_menu();
                }
                break;
            case GAME_RUNNING:
                if (tickCounter % PLAYER_COUNTER_TOTAL == 0) {
                    update_player();
                }

                if (tickCounter % BALL_COUNTER_TOTAL == 0) {
                    refresh_ball();
                    ballSpeedIncrease = update_level();
                    if (ballSpeedIncrease) {
                        set_ball_speed(PACER_RATE, &ballSpeed, &BALL_COUNTER_TOTAL, ballSpeed + ballSpeedIncrease);
                    }
                }

                if (tickCounter % DISPLAY_COUNTER_TOTAL == 0) {
                    display_update();
                }
                break;
            case GAME_END:
                if (tickCounter % DISPLAY_COUNTER_TOTAL == 0) {
                    set_ball_speed(PACER_RATE, &ballSpeed, &BALL_COUNTER_TOTAL, BASE_BALL_SPEED);
                    refresh_end_screen();
                }
                break;
        }
        tickCounter++;
    }
}
