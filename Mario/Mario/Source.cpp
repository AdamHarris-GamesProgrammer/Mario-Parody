#include "Game.h"

int main(int argc, char* argv[])
{
	//Creates a game instance
	Game game;

	//Initializes the game (Enters the game loop)
	game.Initialize();

	//Runs the shutdown which closes SDL 
	game.Shutdown();

	return 0;
}