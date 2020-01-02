#include "Game.h"

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO != 0)) {
		printf("Failed to initialize SDL! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
		printf("Failed to initialize IMG! IMG_Error: %s\n", IMG_GetError());
		return false;
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) != 0) {
		printf("Failed to initialize Mixer! Mixer_Error: %s\n", Mix_GetError());
		return false;
	}

	if (TTF_Init() != 0) {
		printf("Failed to initialize TTF! TTF_Error: %s\n", TTF_GetError());
		return false;
	}

	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, NULL, &mWindow, &mRenderer) != 0) {
		printf("Failed to create window/renderer! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

bool Game::LoadContent()
{


	return true;
}


void Game::RunLoop()
{
	if (LoadContent()) {
		while (!bShouldQuit)
		{
			PollInput();
			Update();
			Render();
		}
	}
	else {
		printf("Failed to load Content!\n");
	}
}


void Game::PollInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			bShouldQuit = true;
		}
		else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				bShouldQuit = true;
				break;
			}
		}
	}
}

void Game::Update()
{

}

void Game::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);



	SDL_RenderPresent(mRenderer);
}


void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mRenderer = NULL;
	mWindow = NULL;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

