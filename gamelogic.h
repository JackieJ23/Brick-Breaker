/** @file   gamelogic.c
    @author Jackie Jone, James Hazelhurst
    @date   17 October 2021
    @brief Game logic for Brick Breaker
*/

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "system.h"
#include <stdint.h>

#define DISPLAY_TEXT_RATE 750
#define BALL_SPEED_INCREASE_AMOUNT 1


// Defining different game states
typedef enum {
    START_MENU,
    GAME_RUNNING,
    GAME_END
} Game_state_t;

/** Updates the players position and changes the positon on the screen. */
void update_player(void);

/** Logic for refreshing the ball's position.
    Checks if the ball is touching the player and bounches the ball off the player. */
void refresh_ball(void);

/** Initalise display text.
    @param rate Rate to set tingyl. */
void display_text_init(uint16_t rate);

/** Set the text to display.
    @param string The string of text to display */
void set_display_text(const char* string);

/** Updates display and moves the message. */
void refresh_display_text(void);

/** Updates the start menu. Needs to be constaly called */
void refresh_start_menu(void);

/** Starts a new game. */
void start_new_game(void);

/** Updates the end screen. Needs to be constantly called */
void refresh_end_screen(void);

/** Gets the current game state
    @return The current state of the game. */
Game_state_t get_game_state(void);

/** Check if it is time to increase the difficulty of the game
    @return value to increase ball speed by. */
uint64_t update_level(void);

/** Updates the speed of the ball .
    @param pacerRate Rate of the pacer loop.
    @param currentBallSpeed Pointer to ball speed to update.
    @param counterTotal Pointer to the counter total to update.
    @param speed Speed to set the current ball speed to. */
void set_ball_speed
(
const uint64_t pacerRate,
uint64_t* currentBallSpeed,
uint64_t* counterTotal,
uint64_t speed
);

#endif
