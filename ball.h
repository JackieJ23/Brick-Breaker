#ifndef BALL_H
#define BALL_H
#include "system.h"

// Ball Structure
typedef struct {
    int8_t colPos;
    int8_t rowPos;
    int8_t colDir;
    int8_t rowDir;

} Ball_t;

/** Create a new ball
    @param colPos Ball column starting position.
    @param rowPos Ball row starting position.
    @param colDir Ball column starting direction: 1 for up, -1 for down.
    @param rowDir Ball row starting direction: 1 for right, -1 for left. */
Ball_t new_ball(int8_t colPos, int8_t rowPos, int8_t colDir, int8_t rowDir);

/** Updates position of ball, must be constantly called
    @param ball pointer to a ball to update the position of. */
void update_ball_pos(Ball_t* ball);

#endif