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
camera follow system
coins
enemies
pow blocks
collider system
main menu
how to play
various levels
screen manager
scoring system
leader board system (fileIO)

*/

/* TEXT SYSTEM
Create a text class that inherits from Actor, and has a TextComponent object attached to it

Text class
+SetText(string text)
+SetTextColor(SDL_Color color)
+GetText()
+GetTextColor()
+SetFont()
+GetFont()
 
 -mColor : SDL_Color
 -mText : std::string
 -mFont : TTF_Font

+LoadTextFromFont(font, string text, ) 

-SDL_Texture text

TextComponent Class inherits from sprite component class 
+SetFont(font)
+LoadFont(const std::string& filename, int pointSize = 24)

*/