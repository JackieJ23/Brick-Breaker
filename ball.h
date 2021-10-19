/** @file   ball.h
    @author Jackie Jone, James Hazelhurst
    @date   17 October 2021
    @brief  Bouncing Ball Module
*/

#ifndef BALL_H
#define BALL_H
#include <stdint.h>

/** Structure defining coordinates or vectors. */
typedef struct {
    int8_t x;
    int8_t y;
} Ball_vect_t;

/** Structure defining position of ball. */
typedef struct {
    Ball_vect_t pos;
    Ball_vect_t dir;
} Ball_t;

/** Create a new ball
    @param colPos Ball column starting position.
    @param rowPos Ball row starting position.
    @param colDir Ball column starting direction: 1 for down, -1 for up.
    @param rowDir Ball row starting direction: 1 for right, -1 for left. */
void ball_init(int8_t colPos, int8_t rowPos, int8_t colDir, int8_t rowDir);

/** Updates position of ball, must be constantly called. */
void update_ball_pos(void);

/** Flips the horizontal direction the ball is going. */
void flip_horiz_ball_dir(void);

/** Flips the verticle direction the ball is going. */
void flip_vert_ball_dir(void);

/** Sets the direction the ball is going
    @param vertDir Verticle direction to set.
    @param horizDir Horitzontal direction to set. */
void change_ball_dir(int8_t vertDir, int8_t horizDir);

/** Gets the position of the ball
    @returns position Position of the ball. */
Ball_vect_t get_ball_position(void);

/** Gets the direction the ball is moving
    @returns Future position of the ball. */
Ball_vect_t get_future_ball_position(void);

/** Gets the direction of the ball
    @returns Direction of the ball. */
Ball_vect_t get_ball_direction(void);

/** Checks if the ball is in a given row
    @param row Row to check if the ball is in.
    @return boolean value whether the ball is in the row or not.*/
bool ball_in_row(uint8_t row);

#endif
