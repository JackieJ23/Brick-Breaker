#include "system.h"
#include "ledmat.h"
#include "display.h"
#include "pacer.h"
#include "pio.h"
#include "pacer.h"
#include "navswitch.h"
#include <stdbool.h>

#define PACER_RATE 500 //Hz

// static uint8_t bitmap[LEDMAT_COLS_NUM] =
// {
//     0xFF, 0xFF, 0xFF, 0xFF, 0xFF
// };







/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};


void config_leds(void)
{
	pio_config_set (LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);


    pio_config_set (LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);

}

void rows_off(void)
{
	pio_output_high(rows[0]);
	pio_output_high(rows[1]);
	pio_output_high(rows[2]);
	pio_output_high(rows[3]);
	pio_output_high(rows[4]);
	pio_output_high(rows[5]);
	pio_output_high(rows[6]);



}

void cols_off(void)
{
	pio_output_high(cols[0]);
	pio_output_high(cols[1]);
	pio_output_high(cols[2]);
	pio_output_high(cols[3]);
	pio_output_high(cols[4]);
}

void display_player (int player_pos)
{
    if (player_pos == 0) {
		rows_off();
		cols_off();
        pio_output_low(cols[0]);
        pio_output_low(cols[1]);
        pio_output_low(rows[6]);
    }

    if (player_pos == 1) {
		rows_off();
		cols_off();
        pio_output_low(cols[1]);
        pio_output_low(cols[2]);
        pio_output_low(rows[6]);
    }

    if (player_pos == 2) {
		rows_off();
		cols_off();
        pio_output_low(cols[2]);
        pio_output_low(cols[3]);
        pio_output_low(rows[6]);

    }
    if (player_pos == 3) {
		rows_off();
		cols_off();
        pio_output_low(cols[3]);
        pio_output_low(cols[4]);
        pio_output_low(rows[6]);
    }
}

void display_ball(int ball_vert, int ball_horz) {
	rows_off();
	cols_off();
	pio_output_low(cols[ball_horz]);
	pio_output_low(rows[ball_vert]);
}

bool check_ball_hit(int player_pos, int ball_horz)
{
	if ((ball_horz == 0 && player_pos == 0)) {
		return false;
	}

	else if (ball_horz == 1) {
		if (player_pos == 1 || player_pos == 0) {
			return false;
		}
		else {
			return true;
		}
	}

	else if (ball_horz == 2) {
		if (player_pos == 1 || player_pos == 2) {
			return false;
		}
		else {
			return true;
		}
	}

	else if (ball_horz == 3) {
		if (player_pos == 2 || player_pos == 3) {
			return false;
		}
		else {
			return true;
		}
	}

	else if ((ball_horz == 4 && player_pos == 3)) {
		return false;
	}

	else {
		return true;
	}
}

int main (void)
{
    //~ uint8_t current_column = 0;

    system_init ();
    pacer_init (500);
    navswitch_init ();

    /* TODO: Initialise LED matrix pins.  */
	config_leds();

	int player_pos = 1;
	int ball_vert = 1;
	int ball_hor = 1;
	int ball_speed = 60;
	int ball_speed_counter = 0;
	bool direction = true; // true is up false is down
	bool right = true;
	bool on_player = true;
	bool game_running = true;



    while (game_running)
    {
        pacer_wait ();



			navswitch_update ();

			if (navswitch_push_event_p (NAVSWITCH_EAST)) {
				if (player_pos >= 3) {
					player_pos = 3;
				} else {
					player_pos++;
				}
			}

			if (navswitch_push_event_p (NAVSWITCH_WEST)) {
				if (player_pos <= 0) {
					player_pos = 0;
				} else {
					player_pos--;
				}
			}

		if (on_player) {

			on_player = false;


			display_player(player_pos);
		} else {

			if (ball_speed_counter == ball_speed) {
				ball_speed_counter = 0;

				if (ball_vert == 0) {
					direction = true;
				} else if (ball_vert == 5) {
					if (check_ball_hit(player_pos, ball_hor)) {
						game_running = false;
					} else {
						direction = false;
					}
				}

				if (ball_hor == 0) {
					right = true;
				} else if (ball_hor == 4) {
					right = false;
				}

				if (right) {
					ball_hor++;
				} else {
					ball_hor--;
				}

				if (direction) {
					ball_vert++;
				} else {
					ball_vert--;
				}



			}
			display_ball(ball_vert, ball_hor);
			on_player = true;
			ball_speed_counter++;
		}
    }
}
