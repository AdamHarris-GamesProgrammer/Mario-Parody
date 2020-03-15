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
	//BlueSky constructor takes in a Game object 
	BlueSky(class Game* gameEntity);
	~BlueSky();

	//Initializes SDL, TTF, Window, Renderer, and Audio
	bool Initialize();

	//Closes all SDL related objects
	void Shutdown();

	//Runs the Game Loop (Input, Update, Render)
	void RunLoop();

	//Adds a Actor that is passed in to the method. Called in the Actor constructor
	void AddActor(class Actor* actor);

	//Removes an Actor that is passed in to the method. Called in the Actor destructor
	void RemoveActor(class Actor* actor);

	//Adds a Sprite that is passed in to the method. Called in the SpriteComponent constructor
	void AddSprite(class SpriteComponent* sprite);

	//Removes a Sprite that is passed in to the method. Called in the SpriteComponent destructor
	void RemoveSprite(class SpriteComponent* sprite);

	//Gets a Texture if it already exists, loads a texture if it has not been loaded before (Stops the same texture from being loaded twice)
	SDL_Texture* GetTexture(const std::string& fileName, bool useColorKey = false);

	//Loads a texture object for text to be loaded onto, takes a file name, font size, text and text color. Called in TextSpriteComponent
	SDL_Texture* GetTextureFromFont(std::string fileName, int pointSize, const std::string& text, SDL_Color textColor);

	//Returns the Renderer
	SDL_Renderer* GetRenderer() { return mRenderer; }

	//Handles input polling (Questions if any input has happened (Key presses, mouse movement). Handles the SDL quit event
	void PollInput();

	//Calls all the update methods from the mActors vector
	void Update();

	//Calls all the render methods from the mSprites vector
	void Render();

	//Unloads Content
	void UnloadContent();

	//Exit condition for the game loop, this is set to true when the player presses escape or the X at the top right of the screen
	bool bShouldQuit = false;
private:
	//Game entity. Used for calling the required methods in the game method
	class Game* mGameEntity;

	//A unordered map is used here to allow me to test if a texture has already been generated (through the use of a string as a key), if it has then the texture is returned if not then the texture is loaded and then placed into this unordered map
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	//Holds all the active Actors
	std::vector<class Actor*> mActors;

	//Holds all the paused actors and moves them to the mActors vector when needed
	std::vector<class Actor*>mPendingActors;

	//Holds all of the sprite objects in the game
	std::vector<class SpriteComponent*> mSprites;

	//a bool variable used to see if actors are currently being updated or not
	bool mUpdatingActors;

	//Used to hold the ticks count from the start of the game (Used to calculate FPS and get the delta time variable for the update methods)
	Uint32 mTicksCount;

	//Holds the renderer used for rendering all objects to the screen
	SDL_Renderer* mRenderer;

	//Holds the window used for displaying the game
	SDL_Window* mWindow;
};

