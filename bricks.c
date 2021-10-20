/** @file   bricks.c
    @author Jackie Jone, James Hazelhurst
    @date   19 October 2021
    @brief  Brick Module
*/
#include <stdint.h>
#include <stdlib.h>
#include "system.h"
#include "bricks.h"
#include "display.h"
#include "ball.h"

/** 2D array contianing all the brick positions*/
static bool brick_array[5][7];


/** Creates a new player with left of player on the given position
    @param colPos Horizontal (column) position to put the player. Left side on position.
    @param rowPos Veritcle (row) position to put the player.
	@param alive Set brick on or off. */
Brick_t brick_init(uint8_t colPos, uint8_t rowPos, bool alive)
{
	Brick_t brick;
    brick.row = rowPos;
    brick.col = colPos;
    brick.is_alive = alive;

	if (alive) {
		display_pixel_set(brick.col, brick.row, true);

	} else {
		display_pixel_set(brick.col, brick.row, false);
	}

    return brick;
}


/** Randomly generates bricks. */
void bricks_init(void)
{
	int randomNumber;

	for (int i=0; i<5; i++) {
	  for (int j=0;j<4;j++) {
		 randomNumber = rand() % 2;
		 brick_array[i][j] = randomNumber;
		 brick_init(i, j, randomNumber); // Brick is returned but nothing is done with it.
	  }
	}

	for (int i=0; i<5; i++) {
	  for (int j=4;j<7;j++) {
		 brick_array[i][j] = false;
		 brick_init(i, j, false);
	  }
	}

}

/** Kills the brick in a given position.
    @param row The row the brick is in.
	@param col The column the brick is in. */
void kill_brick(uint8_t row, uint8_t col)
{
	brick_init(row, col, false);
	brick_array[row][col] = false;
}

/** Checks if a brick has been hit by the ball
    @param futureBallPos Future position of the ball.
	@param ballPos Current position of the ball.
	@param ballDir Direction the ball is going.
	@return Direction to flip the ball.*/
Flip_dir_t ball_hit_brick(Ball_vect_t futureBallPos, Ball_vect_t ballPos, Ball_vect_t ballDir)
{

	bool above = brick_array[ballPos.x][ballPos.y + ballDir.y];
	bool diag = brick_array[futureBallPos.x][futureBallPos.y];
	bool adj = brick_array[ballPos.x + ballDir.x][ballPos.y];

	//~ if (above) {
		//~ kill_brick((ballPos.y + ballDir.y), ballPos.x);
		//~ return 1;
	//~ } else if (diag) {
		//~ kill_brick(futureBallPos.y, futureBallPos.x);
		//~ return 3;
	//~ } else {
		//~ return 0;
	//~ }

	if (above && diag && adj) {
		//kill above and adj
		kill_brick(ballPos.x, ballPos.y + ballDir.y);
		kill_brick(ballPos.x + ballDir.x, ballPos.y);
		return 3;
	} else if (above && adj && !diag) {
		//kill above and adj
		kill_brick(ballPos.x, ballPos.y + ballDir.y);
		kill_brick(ballPos.x + ballDir.x, ballPos.y);
		return 3;
	} else if (!above && diag && !adj) {
		// kill diag
		kill_brick(futureBallPos.x, futureBallPos.y);
		return 3;
	} else if (above && diag && !adj) {
		kill_brick(ballPos.x, ballPos.y + ballDir.y);
		return 1;
	} else if (above && !diag && !adj) {
		// kill above
		kill_brick(ballPos.x, ballPos.y + ballDir.y);
		return 1;
	} else if (!above && diag && adj) {
		// kill adj
		kill_brick(ballPos.x + ballDir.x, ballPos.y);
		return 2;
	} else if (!above && !diag && adj) {
		// kill adj
		kill_brick(ballPos.x + ballDir.x, ballPos.y);
		return 2;
	} else {
		return 0;
	}

	//~ if ((ballPos.y + ballDir.y) == brick.row && ballPos.x == brick.col) {
		//~ return 1;
	//~ } else if (0) {
		//~ return 2;
	//~ } else if (futureBallPos.y == brick.row && futureBallPos.x == brick.col) {
		//~ return 3;
	//~ } else {
		//~ return 0;
	//~ }
}
