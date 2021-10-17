/** @file   ball.c
    @author Jackie Jone, James Hazelhurst
    @date   17 October 2021
    @brief  Bouncing Ball Module
*/

#include <stdint.h>
#include "system.h"
#include "ball.h"

#define ROW_WIDTH LEDMAT_ROWS_NUM
#define COL_WIDTH LEDMAT_COLS_NUM


/** Create a new ball
    @param colPos Ball column starting position.
    @param rowPos Ball row starting position.
    @param colDir Ball column starting direction: 1 for down, -1 for up.
    @param rowDir Ball row starting direction: 1 for right, -1 for left.
    @return new ball object */
Ball_t new_ball(int8_t colPos, int8_t rowPos, int8_t colDir, int8_t rowDir)
{
    Ball_t newBall =
    {
        .colPos = colPos,
        .rowPos = rowPos,
        .colDir = colDir,
        .rowDir = rowDir
    };

    return newBall;
}

/** Updates position of ball, must be constantly called
    @param ball pointer to a ball to update the position of. */
void update_ball_pos(Ball_t* ball)
{
    // Increases the balls co-ordinates by the balls speed.
    ball->colPos += ball->colDir;
    ball->rowPos += ball->rowDir;

    // Checking if the ball has hit an edge of the screen.
    if (ball->colPos >= COL_WIDTH - 1 || ball->colPos <= 0) {
        flip_horiz_ball_dir(ball);
    }

    if (ball->rowPos >= ROW_WIDTH - 1 || ball->rowPos <= 0) {
        flip_vert_ball_dir(ball);
    }
}

/** Flips the horizontal direction the ball is going
    @param ball Pointer to a ball. */
void flip_horiz_ball_dir(Ball_t* ball)
{
    ball->colDir = -(ball->colDir);
}

/** Flips the verticle direction the ball is going
    @param ball Pointer to a ball. */
void flip_vert_ball_dir(Ball_t* ball)
{
    ball->rowDir = -(ball->rowDir);
}

/** Sets the direction the ball is going
    @param ball Pointer to a ball.
    @param vertDir Verticle direction to set.
    @param horizDir Horitzontal direction to set. */
void change_ball_dir(Ball_t* ball, int8_t vertDir, int8_t horizDir)
{
    ball->colDir = horizDir;
    ball->rowDir = vertDir;
}
