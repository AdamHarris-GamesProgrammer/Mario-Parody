#include "Sound.h"

Sound::Sound()
{

}

Sound::~Sound()
{

}

Mix_Chunk* Sound::LoadSoundEffect(std::string filePath)
{
	mSound = nullptr;
	//Loads the sound
	mSound = Mix_LoadWAV(filePath.c_str());
	if (!mSound) { //if mSound is equal to null
		printf("Could not load %s\nMix Error: %s", filePath.c_str(), Mix_GetError()); //output error
	}
	//return mSound
	return mSound;
}

void Sound::PlaySoundEffect(Mix_Chunk* sound)
{
	//plays the sound that is passed and does not loop
	Mix_PlayChannel(-1, sound, 0);
}
