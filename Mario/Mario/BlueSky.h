#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

class BlueSky
{
public:
	BlueSky(class Game* gameEntity);
	~BlueSky();

	bool Initialize();

	void Shutdown();

	void RunLoop();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName, bool useColorKey = false);

	SDL_Texture* GetTextureFromFont(std::string fileName, int pointSize, const std::string& text, SDL_Color textColor);

	SDL_Renderer* GetRenderer() { return mRenderer; }

	void PollInput();

	void Update();

	void Render();

	void LoadContent();
	void UnloadContent();

	bool bShouldQuit = false;
private:
	class Game* mGameEntity;

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<class Actor*> mActors;

	std::vector<class Actor*>mPendingActors;

	std::vector<class SpriteComponent*> mSprites;

	bool mUpdatingActors;

	Uint32 mTicksCount;

	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;
};

