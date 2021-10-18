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

// Defining pacer and update rates.
#define PACER_RATE 500
#define PLAYER_UPDATE_RATE 50
#define DISPLAY_UPDATE_RATE 500




int main(void)
{
    // Initilise system.
    system_init();
    pacer_init(PACER_RATE);
    navswitch_init();
    display_init();


    // Initalisations can be added to a new_game() function in the gamelogic.c module.
    // Create new ball
    ball_init(0, 3, 1, 1);
    player_init(2, 6);


    uint64_t ballSpeed = 2;
    uint64_t BALL_COUNTER_TOTAL = PACER_RATE/ballSpeed;
    uint64_t PLAYER_COUNTER_TOTAL = PACER_RATE/PLAYER_UPDATE_RATE;
    uint64_t tickCounter = 0;


    while(true)
    {
        pacer_wait();

        if (tickCounter % PLAYER_COUNTER_TOTAL == 0) {
            navswitch_update();
            update_player();
        }

        if (tickCounter % BALL_COUNTER_TOTAL == 0) {
            refresh_ball();
        }

        // if (Counter % 1 == 0) {
        //     display_update();
        // }
        display_update();
        tickCounter++;
    }
}
