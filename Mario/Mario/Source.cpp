#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;

	if (game.Initialize()) {
	}

	game.Shutdown();

	return 0;
}