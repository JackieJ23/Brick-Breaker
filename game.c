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

#define PACER_RATE 1500 //Hz

#define PLAYER_UPDATE_RATE 40
#define PLAYER_COUNTER_TOTAL PACER_RATE/PLAYER_UPDATE_RATE

#define BALL_UPDATE_RATE 40
#define BALL_COUNTER_TOTAL PACER_RATE/BALL_UPDATE_RATE



int main(void)
{
    // Initilise system
    system_init();
    pacer_init(500);
    navswitch_init();
    display_init();


    // Initalisations can be added to a new_game() function in the gamelogic.c module.
    // Create new ball
    ball_init(0, 3, 1, 1);
    player_init(2, 6);

    uint64_t playerUpdateCounter = 0;
    uint64_t ballUpdateCounter = 0;
    uint64_t DisplayUpdateCounter = 0;

    while(true)
    {
        pacer_wait();

        if (playerUpdateCounter >= PLAYER_COUNTER_TOTAL) {
            navswitch_update();
            update_player();
            playerUpdateCounter = 0;
        }
        playerUpdateCounter++;

        if (playerUpdateCounter >= BALL_COUNTER_TOTAL) {
            refresh_ball();
            ballUpdateCounter = 0;
        }
        ballUpdateCounter++;

        if (DisplayUpdateCounter >= 500) {
            display_update();
        }
        DisplayUpdateCounter++;
        // display_update();
    }
}
