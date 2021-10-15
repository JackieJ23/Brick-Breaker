#include <stdint.h>
#include "system.h"
#include "ball.h"

#define ROW_WIDTH LEDMAT_ROWS_NUM
#define COL_WIDTH LEDMAT_COLS_NUM


/** Create a new ball
    @param colPos Ball column starting position.
    @param rowPos Ball row starting position.
    @param colDir Ball column starting direction: 1 for up, -1 for down.
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
    ball->colPos += ball->colDir;
    ball->rowPos += ball->rowDir;

    if (ball->colPos >= COL_WIDTH - 1) {
        ball->colDir = -1;
    } else if (ball->colPos <= 0) {
        ball->colDir = 1;
    }

    if (ball->rowPos >= ROW_WIDTH - 1) {
        ball->rowDir = -1;
    } else if (ball->rowPos <= 0) {
        ball->rowDir = 1;
    }
}
