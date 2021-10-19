/** @file   player.h
    @author Jackie Jone, James Hazelhurst
    @date   17 October 2021
    @brief  2 Pixel player bar module
*/

#ifndef BRICKS_H
#define BRICKS_H
#include <stdint.h>
#include "ball.h"

/** Structure defining position of player. */
typedef struct {
	uint8_t col;
    uint8_t row;
    bool is_alive;
} Brick_t;


Brick_t brick_init(uint8_t colPos, uint8_t rowPos, bool alive);

void bricks_init(void);

void kill_brick(uint8_t row, uint8_t col);

int ball_hit_brick(Ball_vect_t futureBallPos, Ball_vect_t ballPos, Ball_vect_t ballDir);



#endif

