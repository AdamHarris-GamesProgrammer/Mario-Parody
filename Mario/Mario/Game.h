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

	SDL_Texture* GetTextureFromFont(std::string fileName, int pointSize, const std::string& text, SDL_Color textColor);

	SDL_Renderer* GetRenderer() { return mRenderer; }


	//game specific code
	class Mario* GetPlayer() { return player; }

	class TileMapComponent* GetMap() { return map; }

	void AddCoin(class Coin* coin);
	void RemoveCoin(class Coin* coin);
	std::vector<class Coin*>& GetCoins() { return mCoins; }

private:
	void LoadContent();
	void UnloadContent();

	void PollInput();

	void Update();

	void Render();


	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;

	std::unordered_map<std::string, SDL_Texture*> mTextures;
	std::unordered_map<std::string, TTF_Font*> mFontTextures;

	std::vector<class Actor*> mActors;

	std::vector<class Actor*>mPendingActors;

	std::vector<class SpriteComponent*> mSprites;

	Uint32 mTicksCount;
	bool bShouldQuit;
	bool mUpdatingActors;


	//Game specific code
	class Mario* player;
	class Actor* mapActor;
	class TileMapComponent* map;

	class Actor* bgActor;
	class Actor* fgActor;

	std::vector<class Coin*> mCoins;

	Actor* scoreText;
	class TextSpriteComponent* scoreTsc;

	int score = 0;
};

