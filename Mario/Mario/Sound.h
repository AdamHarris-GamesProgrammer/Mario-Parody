#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>

class Sound
{
public:
	Sound();
	~Sound();

	Mix_Chunk* LoadSoundEffect(std::string filePath);
	void PlaySoundEffect(Mix_Chunk* sound);

private:
	Mix_Chunk* mSound;
};

