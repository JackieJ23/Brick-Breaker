/** @file   bricks.h
    @author Jackie Jone, James Hazelhurst
    @date   19 October 2021
    @brief  Brick Module
*/

#ifndef BRICKS_H
#define BRICKS_H
#include <stdint.h>
#include "ball.h"

/** Structure defining position and status of a brick */
typedef struct {
	uint8_t col;
    uint8_t row;
    bool is_alive;
} Brick_t;

/** Creates a new brick on the given position.
    @param colPos Horizontal (column) position to put the brick.
    @param rowPos Veritcle (row) position to put the brick.
	@param alive Set brick on or off. */
Brick_t brick_init(uint8_t colPos, uint8_t rowPos, bool alive);

/** Randomly generates bricks. */
void bricks_init(void);

/** Kills the brick in a given position.
    @param row The row the brick is in.
	@param col The column the brick is in. */
void kill_brick(uint8_t row, uint8_t col);

/** Checks if a brick has been hit by the ball
    @param futureBallPos Future position of the ball.
	@param ballPos Current position of the ball.
	@param ballDir Direction the ball is going.
	@return Direction to flip the ball.*/
Flip_dir_t ball_hit_brick(Ball_vect_t futureBallPos, Ball_vect_t ballPos, Ball_vect_t ballDir);

/** Checks if there are any more bricks in the current game.
    @return Boolean value wether there are bricks in the game or not. */
bool bricks_remaining(void);

#endif
