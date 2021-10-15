#include "system.h"
#include "ledmat.h"
#include "display.h"
#include "pacer.h"

#define PACER_RATE 500 //Hz

// static uint8_t bitmap[LEDMAT_COLS_NUM] =
// {
//     0xFF, 0xFF, 0xFF, 0xFF, 0xFF
// };

int main (void)
{
    system_init ();
    display_init();
    pacer_init(PACER_RATE);


    display_pixel_set(3, 3, 1);
    while (1)
    {
        pacer_wait();

        display_update();
    }
}
