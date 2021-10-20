/** @file   ball.c
    @author Jackie Jone, James Hazelhurst
    @date   17 October 2021
    @brief  Bouncing Ball Module
*/

#include <stdint.h>
#include <stdbool.h>
#include "system.h"
#include "ball.h"
#include "display.h"

#define ROW_WIDTH LEDMAT_ROWS_NUM
#define COL_WIDTH LEDMAT_COLS_NUM

static Ball_t ball;

/** Create a new ball
    @param colPos Ball column starting position.
    @param rowPos Ball row starting position.
    @param colDir Ball column starting direction: 1 for down, -1 for up.
    @param rowDir Ball row starting direction: 1 for right, -1 for left. */
void ball_init(int8_t colPos, int8_t rowPos, int8_t colDir, int8_t rowDir)
{
    ball.pos.x = colPos;
    ball.pos.y = rowPos;
    ball.dir.x = colDir;
    ball.dir.y = rowDir;
    display_pixel_set(ball.pos.x, ball.pos.y, true);
}

/** Updates position of ball, must be constantly called */
void update_ball_pos(void)
{
    // Turn off pixel in previous position.
    display_pixel_set(ball.pos.x, ball.pos.y, false);

    // Increases the balls co-ordinates by the balls speed.
    ball.pos.x += ball.dir.x;
    ball.pos.y += ball.dir.y;



    // Checking if the ball has hit an edge of the screen.
    // Left and right edges.
    
    
    if (ball.pos.x >= COL_WIDTH - 1) {
        ball.pos.x = COL_WIDTH - 1;
        flip_horiz_ball_dir();
    } else if (ball.pos.x <= 0) {
        ball.pos.x = 0;
        flip_horiz_ball_dir();
    }

    // Top and bottom edges
    if (ball.pos.y >= ROW_WIDTH - 1) {
        ball.pos.y = ROW_WIDTH - 1;
        flip_vert_ball_dir();
    } else if (ball.pos.y <= 0) {
        ball.pos.y = 0;
        flip_vert_ball_dir();
    }

    // Turn on pixel in new position.
    display_pixel_set(ball.pos.x, ball.pos.y, true);
}

/** Flips the horizontal direction the ball is going. */
void flip_horiz_ball_dir(void)
{
    ball.dir.x = -(ball.dir.x);
}

/** Flips the verticle direction the ball is going. */
void flip_vert_ball_dir(void)
{
    ball.dir.y = -(ball.dir.y);
}

/** Sets the direction the ball is going
    @param vertDir Verticle direction to set.
    @param horizDir Horitzontal direction to set. */
void change_ball_dir(int8_t vertDir, int8_t horizDir)
{
    ball.dir.x = horizDir;
    ball.dir.y = vertDir;
}

/** Gets the position of the ball
    @returns Position of the ball. */
Ball_vect_t get_ball_position(void)
{
    return ball.pos;
}

/** Gets the direction the ball is moving
    @returns Future position of the ball. */
Ball_vect_t get_future_ball_position(void)
{
    Ball_vect_t futurePos = {
        .x = ball.pos.x + ball.dir.x,
        .y = ball.pos.y + ball.dir.y
    };
    return futurePos;
}

/** Gets the direction of the ball
    @returns Direction of the ball. */
Ball_vect_t get_ball_direction(void)
{
	return ball.dir;
}




/** Checks if the ball is in a given row
    @param row Row to check if the ball is in.
    @return boolean value whether the ball is in the row or not.*/
bool ball_in_row(uint8_t row)
{
    return ball.pos.y == row;
}
