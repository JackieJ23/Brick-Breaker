/** @file   player.c
    @author Jackie Jone, James Hazelhurst
    @date   17 October 2021
    @brief  2 Pixel player bar module
*/
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "system.h"
#include "bricks.h"
#include "ball.h"
#include "display.h" // TODO: include display in Makefile.



static bool brick_array[5][7];


/** Creates a new player with left of player on the given position
    @param colPos Horizontal (column) position to put the player. Left side on position.
    @param rowPos Veritcle (row) position to put the player. */
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


void bricks_init()
{
	
	int number;
	
	for (int i=0; i<5; i++) {
	  for (int j=0;j<4;j++) {
		 number = rand() % 2;
		 brick_array[i][j] = number;
		 brick_init(i, j, number);
	  }
	}
	for (int i=0; i<5; i++) {
	  for (int j=4;j<7;j++) {
		 brick_array[i][j] = false;
		 brick_init(i, j, false);
	  }
	}
	
}

void kill_brick(uint8_t row, uint8_t col)
{
	brick_init(row, col, false);
	brick_array[row][col] = false;
}

int ball_hit_brick(Ball_vect_t futureBallPos, Ball_vect_t ballPos, Ball_vect_t ballDir)
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
		kill_brick(ballPos.x, ballPos.y + ballDir.y);
		kill_brick(ballPos.x + ballDir.x, ballPos.y);
		return 3;
	} else if (above && adj && !diag) {
		//kill above and adj
		kill_brick(ballPos.x, ballPos.y + ballDir.y);
		kill_brick(ballPos.x + ballDir.x, ballPos.y);
		return 3;
	} else if (!above && diag && !adj) {
		//~ // kill diag
		kill_brick(futureBallPos.x, futureBallPos.y);
		return 3;
	} else if (above && diag && !adj) {
		kill_brick(ballPos.x, ballPos.y + ballDir.y);
		return 1;
	} else if (above && !diag && !adj) {
		kill_brick(ballPos.x, ballPos.y + ballDir.y);
		//kill above
		return 1;
	} else if (!above && diag && adj) {
		kill_brick(ballPos.x + ballDir.x, ballPos.y);
		return 2;
	} else if (!above && !diag && adj) {
		//kill adj
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
