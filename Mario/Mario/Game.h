#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

class Game
{
public:
	Game() {}
	~Game() {}

	bool Initialize();

	void Shutdown();

	void RunLoop();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName, bool useColorKey = false);

	SDL_Renderer* GetRenderer() { return mRenderer; }
private:
	void LoadContent();
	void UnloadContent();

	void PollInput();

	void Update();

	void Render();


	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<class Actor*> mActors;

	std::vector<class Actor*>mPendingActors;

	std::vector<class SpriteComponent*> mSprites;

	Uint32 mTicksCount;
	bool bShouldQuit;
	bool mUpdatingActors;

	class Mario* player;
};

