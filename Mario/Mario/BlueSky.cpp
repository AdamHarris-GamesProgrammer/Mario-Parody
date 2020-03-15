#include "BlueSky.h"

#include "ComponentsList.h"
#include "Game.h"

BlueSky::BlueSky(Game* gameEntity) : mGameEntity(gameEntity) {} //Initializes the mGameEntity variable

BlueSky::~BlueSky() {}

bool BlueSky::Initialize()
{
	//Tests to see if video and audio have been initialized 
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO != 0)) {
		printf("Failed to initialize SDL! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Tests to see if the IMG library has been initialized
	int imgFlags = IMG_INIT_PNG;
	if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
		printf("Failed to initialize IMG! IMG_Error: %s\n", IMG_GetError());
		return false;
	}

	//Tests to see if SDL_Mixer has been initialized
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
		printf("Failed to initialize Mixer! Mixer_Error: %s\n", Mix_GetError());
		return false;
	}

	//Tests to see if SDL_TTF has been initialized
	if (TTF_Init() != 0) {
		printf("Failed to initialize TTF! TTF_Error: %s\n", TTF_GetError());
		return false;
	}

	//Creates the window and renderer and tests to see if they have been initialized
	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, NULL, &mWindow, &mRenderer) != 0) {
		printf("Failed to create window/renderer! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Gets the current tick count once SDL has been fully initialized
	mTicksCount = SDL_GetTicks();

	//If the program has got to here then everything was initialized properly so return true
	return true;
}

void BlueSky::Shutdown()
{
	//Unloads all sprites and actors in the game
	UnloadContent();
	
	//Destroys the renderer
	SDL_DestroyRenderer(mRenderer);

	//Destroys the window
	SDL_DestroyWindow(mWindow);
	
	//Quits all of the SDL Libraries that have been initialized
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void BlueSky::RunLoop()
{
	while (!bShouldQuit)
	{
		//Calls the input, update and render methods of the game entity object
		mGameEntity->PollInput();
		mGameEntity->Update();
		mGameEntity->Render();
	}
}

void BlueSky::AddActor(class Actor* actor)
{
	//if in the process of updating actors then the new actor needs to be added to pending
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
}

void BlueSky::RemoveActor(class Actor* actor)
{
	//Is the actor in the pending actors vector
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end()) {
		//swaps the actor to the end of the vector and then erases it
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	//Is the actor in the actors vector
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()) {
		//swaps the actor to the end of the vector and then erases it
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void BlueSky::AddSprite(class SpriteComponent* sprite)
{
	//gets the draw order for the sprite passed in
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter) {
		//if the draw order is lower than the current sprite...
		if (myDrawOrder < (*iter)->GetDrawOrder()) {
			//... break out of loop
			break;
		}
	}

	//Insert this sprite before the next one
	mSprites.insert(iter, sprite);
}

void BlueSky::RemoveSprite(class SpriteComponent* sprite)
{
	//Finds the sprite that is passed into the method
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	//Removes the sprite from the mSprites vector
	mSprites.erase(iter);
}

SDL_Texture* BlueSky::GetTexture(const std::string& fileName, bool useColorKey /*= false*/)
{
	SDL_Texture* tex = nullptr;

	//is the texture in the mTextures map
	auto iter = mTextures.find(fileName);
	//if the texture has been found
	if (iter != mTextures.end()) {
		//sets the tex variable equal to the texture thats been found
		tex = iter->second;
	}
	else {
		//loads the image onto a SDL_Surface
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf) {
			printf("Failed to load texture file %s! IMG_Error: %s\n", fileName.c_str(), IMG_GetError());
			return nullptr;
		}

		//if the colour key had been enabled
		SDL_SetColorKey(surf, useColorKey, SDL_MapRGB(surf->format, 0xFF, 0xFf, 0xFF));

		//creates a texture from the surf variable
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);

		//Deletes the old surf
		SDL_FreeSurface(surf);

		//Tests to see if the tex variable has a value
		if (!tex) {
			printf("Failed to make texture out of surface %s! IMG_Error: %s\n", fileName.c_str(), IMG_GetError());
			return nullptr;
		}

		//puts the tex variable into the mTextures map meaning that it wont be loaded again
		mTextures.emplace(fileName.c_str(), tex);
	}
	//returns the tex variable
	return tex;
}

SDL_Texture* BlueSky::GetTextureFromFont(std::string fileName, int pointSize, const std::string& text, SDL_Color textColor)
{
	//creates a blank texture and font variable
	SDL_Texture* tex = nullptr;
	TTF_Font* font = nullptr;

	//sets the font equal to the loaded font with the desired size
	font = TTF_OpenFont(fileName.c_str(), pointSize);

	//Creates a surface for the font to be loaded onto 
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

	//Tests to see if the textSurface has a value
	if (!textSurface) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		//Creates a texture from the textSurface variable
		tex = SDL_CreateTextureFromSurface(mRenderer, textSurface);

		//Tests to see if the tex variable has a value
		if (!tex) {
			printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
		}

		//Deletes the testSurface variable now that it has served its use
		SDL_FreeSurface(textSurface);
	}

	//returns the texture
	return tex;
}

void BlueSky::PollInput()
{
	//Creates a SDL_Event to see what events have taken place in the past frame
	SDL_Event e;

	//if events took place (e.g. Key presses or mouse movement)
	while (SDL_PollEvent(&e) != 0) {
		//If the X button has been pressed
		if (e.type == SDL_QUIT) {
			bShouldQuit = true;
		}

		//if the event is of type SDL_Keydown
		else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym)
			{
				//if the event is the player pressing the escape key
			case SDLK_ESCAPE:
				//Set bShouldQuit to true, quits the game at the end of the current frame
				bShouldQuit = true;
				break;
			}
		}

	}
}

void BlueSky::Update()
{
	//Holds the game still until 16ms have passed. This creates 60fps game play (16ms = 1000 / 60)
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16)); //delays the game 16ms, creating (roughly) 60fps game play

	//calculates delta time
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	//Gets the tick count again 
	mTicksCount = SDL_GetTicks();

	//update all actors
	mUpdatingActors = true;
	for (auto actor : mActors) {
			actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	//moves pending actors into mActors
	for (auto pending : mPendingActors) {
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	//Adds any dead actors to a temporary vector to be removed
	std::vector<Actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->GetState() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}

	//deletes any dead actors from deadActor, this also deletes them from mActors
	for (auto actor : deadActors) {
		delete actor;
	}
}

void BlueSky::Render()
{
	//Sets the rendering colour to white if an object is not present there
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//Clears the screen
	SDL_RenderClear(mRenderer);

	//Cycles through each sprite in the mSprites vector
	for (auto sprite : mSprites) {
		//Checks to see if the sprite is active
		if (sprite->GetOwner()->GetState() == Actor::EActive) {
			//Draws the sprite to the screen
			sprite->Draw(mRenderer);

		}
	}
	//Presents the renderer to the player
	SDL_RenderPresent(mRenderer);
}

void BlueSky::UnloadContent()
{
	//deletes Actors
	while (!mActors.empty()) {
		delete mActors.back();
	}

	//Destroys textures
	for (auto i : mTextures) {
		SDL_DestroyTexture(i.second);
	}

	//clears the mTextures map
	mTextures.clear();
}
