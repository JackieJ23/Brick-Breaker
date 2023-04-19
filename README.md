Author Jackie Jone, James Hazelhurst

Date 21 October 2021 (Updated April 2023)

# Brick Breaker
Brick breaker is a game (based on Atari Breakout) where the player controls a horizontal bar moving left and right trying to keep a ball from hitting the bottom of the screen. To progress throughout the game, the player must bounce the ball off the bar to break bricks in the top half of the screen. When all the bricks are cleared, new bricks are generated and the speed of the ball increases thus increasing the difficulty of the game.

When the program starts, the player is presented a message displaying the game name.
When the navigation switch is pushed down, the game starts and the player can
control the bar by pushing the navigation switch to the left and right.
Once the game ends, when the ball hits the bottom of the screen, a game over message
is displayed. The navigation switch can be pressed down again to get back to the
start screen.

Controls:
Navigation switch down         - Start game/Navigate menus.
Navigation switch left (West)  - Move bar left.
Navigation switch right (East) - Move bar right.

## Micro controller
This game was designed to be played on a Atmega32u2 micro controller with a 5x7 LED display with push button and nav switch for control. The Atmega32u2 was attached to a UC Funkit 4 made by the University of Canterbury.

The driver files specific to the microcontroller and UC Funkit board is needed to compile the program.

dfu programmer is required to flash the program onto the microcontroller.

To compile and flash the program, open a terminal in the root of the project and run ```make program```.