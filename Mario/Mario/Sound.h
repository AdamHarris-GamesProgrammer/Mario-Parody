#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>

class Sound
{
public:
	Sound();
	~Sound();
	//Loads a sound effect
	Mix_Chunk* LoadSoundEffect(std::string filePath);

	//Plays a sound effect
	void PlaySoundEffect(Mix_Chunk* sound);

private:
	Mix_Chunk* mSound;
};

