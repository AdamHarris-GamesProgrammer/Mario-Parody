#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "Constants.h"

#include <iostream>

class Game
{
public:
	Game() {}
	~Game() {}

	bool Initialize();

	void Shutdown();

	void RunLoop();
private:
	bool LoadContent();

	void PollInput();

	void Update();

	void Render();

	bool bShouldQuit = false;


	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;

	
};

