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
#include "gamelogic.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "bricks.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define START_MENU_MESSAGE "BRICK BREAKER"
#define GAME_OVER_MESSAGE "GAME OVER SCORE "
#define DEFAULT_PLAYER_COL 2
#define DEFAULT_PLAYER_ROW 6

#define DEFAULT_BALL_COL 2
#define DEFAULT_BALL_ROW 5
#define DEFAULT_BALL_X_DIR -1
#define DEFAULT_BALL_Y_DIR -1

#define END_MESSAGE_LEN 40
#define SCORE_STR_LEN 3
#define BASE_TEN 10


// Defining state of the game.
static Game_state_t GAME_STATE = START_MENU;
// Defining whether the scrolling text has been updated.
static bool UPDATED_TEXT = false;

// Score counter
static int SCORE = 0;
static 	char SCORE_STR[SCORE_STR_LEN];


/** Initalise display text.
    @param rate Rate to set tingyl. */
void display_text_init(uint16_t rate)
{
    tinygl_init(rate);
    tinygl_font_set(&font3x5_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
}

/** Set the text to display
    @param string The string of text to display. */
void set_display_text(const char* string)
{
    display_clear();
    display_update();
    tinygl_text(string);
}

/** Updates display and moves the message. */
void refresh_display_text(void)
{
    tinygl_update();
}

/** Gets the current game state
    @return The current state of the game. */
Game_state_t get_game_state(void)
{
    Game_state_t currentGameState = GAME_STATE;
    return currentGameState;
}

/** Updates the players position and changes the positon on the screen. */
void update_player(void)
{
    navswitch_update();
    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        move_player_right();
    }

    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        move_player_left();
    }
}

/** Logic for refreshing the ball's position.
    Checks if the ball is touching the player and bounches the ball off the player. */
void refresh_ball(void)
{
    Ball_vect_t ballPos = get_ball_position();
    Ball_vect_t ballDir = get_ball_direction();
    Ball_vect_t futureBallPos = get_future_ball_position();
    Player_t playerPos = get_player_position();

    // End the game.
    if (ballPos.y >= LEDMAT_ROWS_NUM - 1) {
        display_clear();
        display_pixel_set(0, 0, 1);
        display_update();
        GAME_STATE = GAME_END;
    }

    // Checking if a ball hits a brick
    Flip_dir_t flipBallDir = ball_hit_brick(futureBallPos, ballPos, ballDir);
    switch (flipBallDir) {
        default:
        case DONT_FLIP:
            break;
        case FLIP_VERT:
		    flip_vert_ball_dir();
            break;
        case FLIP_HORIZ:
            flip_horiz_ball_dir();
            break;
        case FLIP_VERT_AND_HORIZ:
            flip_vert_ball_dir();
            flip_horiz_ball_dir();
            break;
    }

    // Ball is in the row above the player.
    if (ballPos.y == playerPos.pRow - 1 && futureBallPos.y > ballPos.y) {
		if (ballPos.x == 4 && (playerPos.pRight == 4 || playerPos.pRight == 3)) {
			change_ball_dir(-1, -1);

		} else if (ballPos.x == 0 && (playerPos.pLeft == 0 || playerPos.pLeft == 1)) {
			change_ball_dir(-1, 1);

		} else {
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

            // Ball is coming towards the right player pixel from the top right corner.
            } else if (futureBallPos.x == playerPos.pRight) {
                change_ball_dir(-1, 1);
            }
        }
    }

    update_ball_pos();
}

/** Sets up display for a new game. */
void start_new_game(void)
{
    // Create new ball and initalise player.
    display_clear();
    display_update();
    bricks_init();
    ball_init(DEFAULT_BALL_COL, DEFAULT_BALL_ROW, DEFAULT_BALL_X_DIR, DEFAULT_BALL_Y_DIR);
    player_init(DEFAULT_PLAYER_COL, DEFAULT_PLAYER_ROW);
    SCORE = 0;

}

/** Updating start menu. */
void refresh_start_menu(void)
{
    if (!UPDATED_TEXT) {
        display_clear();
        display_update();
        set_display_text(START_MENU_MESSAGE);
        UPDATED_TEXT = true;
    }

    refresh_display_text();

    navswitch_update();
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        start_new_game();
        UPDATED_TEXT = false;
        GAME_STATE = GAME_RUNNING;
    }
}

/** Updating end screen. */
void refresh_end_screen()
{
	//SCORE_STR = {0};
	char end_message[END_MESSAGE_LEN] = GAME_OVER_MESSAGE;
	itoa(SCORE, SCORE_STR, BASE_TEN);
	strcat(end_message, SCORE_STR);

    if (!UPDATED_TEXT) {
        display_text_init(DISPLAY_TEXT_RATE);
        set_display_text(end_message);
        UPDATED_TEXT = true;
    SCORE_STR[0] = '0';
    SCORE_STR[1] = 0;
    }

    refresh_display_text();


    navswitch_update();
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        UPDATED_TEXT = false;
        GAME_STATE = START_MENU;
    }
}



/** Check if it is time to increase the difficulty of the game
    @return value to increase ball speed by. */
uint64_t update_level(void)
{
    Ball_vect_t ballPos = get_ball_position();
    if (ballPos.y >= MAX_BRICK_DEPTH && !bricks_remaining()) {
        bricks_init();
        SCORE++;
        return BALL_SPEED_INCREASE_AMOUNT;
    }
    return 0;
}

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
)
{
    *currentBallSpeed = speed;
    *counterTotal = pacerRate / (*currentBallSpeed);
}
