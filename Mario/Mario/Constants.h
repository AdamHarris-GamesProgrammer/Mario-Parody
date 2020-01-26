#pragma once

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 640
#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define JUMP_FORCE_DECREMENT	400.0f
#define INITIAL_JUMP_FORCE		400.0f
#define INITIAL_JUMP_FORCE_SMALL 200.0f

#define GRAVITY 96.0f


/*TODO
dynamically sizing a map based on the width of the map loaded
level completion/ failure
camera component class
enemies
pow blocks
collier system
main menu
how to play
scoring system (highscore for each level, leader boards etc player can input there name as well)
leader board system (fileIO)
FIX JUMPING AND COLLISION
*/

/* Collision values
-1 = air
0 = bricks
1 = coins
2 = gold bricks
3 = level goal*/