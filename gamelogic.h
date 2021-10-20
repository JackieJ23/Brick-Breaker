#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "system.h"
#include <stdint.h>

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
#endif
