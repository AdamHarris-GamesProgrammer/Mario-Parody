#pragma once

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 640
#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define JUMP_FORCE_DECREMENT	400.0f
#define INITIAL_JUMP_FORCE		500.0f
#define INITIAL_JUMP_FORCE_SMALL 100.0f

#define GRAVITY 192.0f


/*TODO
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
0 = ground
1 = floating bricks
2 = coins
3 = gold bricks
4 = level goal*/