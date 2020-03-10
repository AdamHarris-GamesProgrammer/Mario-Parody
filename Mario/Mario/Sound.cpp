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

	mSound = Mix_LoadWAV(filePath.c_str());
	if (!mSound) {
		printf("Could not load %s\nMix Error: %s", filePath.c_str(), Mix_GetError());
	}

	return mSound;
}

void Sound::PlaySoundEffect(Mix_Chunk* sound)
{
	Mix_PlayChannel(-1, sound, 0);
}
