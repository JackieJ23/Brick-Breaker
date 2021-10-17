/** @file   ball.h
    @author Jackie Jone, James Hazelhurst
    @date   17 October 2021
    @brief  Bouncing Ball Module
*/

#ifndef BALL_H
#define BALL_H
#include <stdint.h>

/** Structure defining position of ball */
typedef struct {
    int8_t colPos;
    int8_t rowPos;
    int8_t colDir;
    int8_t rowDir;
} Ball_t;

/** Create a new ball
    @param colPos Ball column starting position.
    @param rowPos Ball row starting position.
    @param colDir Ball column starting direction: 1 for down, -1 for up.
    @param rowDir Ball row starting direction: 1 for right, -1 for left.
    @return New ball object. */
Ball_t new_ball(int8_t colPos, int8_t rowPos, int8_t colDir, int8_t rowDir);

/** Updates position of ball, must be constantly called
    @param ball pointer to a ball to update the position of. */
void update_ball_pos(Ball_t* ball);

/** Flips the horizontal direction the ball is going
    @param ball Pointer to a ball. */
void flip_horiz_ball_dir(Ball_t* ball);

/** Flips the verticle direction the ball is going
    @param ball Pointer to a ball. */
void flip_vert_ball_dir(Ball_t* ball);


/** Sets the direction the ball is going
    @param ball Pointer to a ball.
    @param vertDir Verticle direction to set.
    @param horizDir Horitzontal direction to set. */
void change_ball_dir(Ball_t* ball, int8_t vertDir, int8_t horizDir);

#endif
