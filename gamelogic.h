#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "system.h"
#include <stdint.h>


/** Updates the players position and changes the positon on the screen. */
void update_player(void);


/** Updates the display of the whole game by iterating through the gameMap and
    changing the values on the display.c module's own bitmap to be displayed
    could be slow.
    Note: Not needed if directly updating display.c module's bitmap in ball and
    player refersh/update code.
*/
// void game_update_display();

void refresh_ball(void);

#endif
