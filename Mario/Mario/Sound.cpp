#include "Sound.h"

Sound::Sound(bool loop /*= false*/)
{
	mLooping = loop;
}

Sound::~Sound()
{
	Mix_FreeChunk(mSoundEffect);
	mSoundEffect = NULL;
}

void Sound::Load(std::string filePath)
{
	mSoundEffect = Mix_LoadWAV(filePath.c_str());
	if (!mSoundEffect) {
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void Sound::Play()
{
	Mix_PlayChannel(-1, mSoundEffect, mLooping);
}

void Sound::Pause()
{
	Mix_Pause(-1);
}

void Sound::Resume()
{
	Mix_Resume(-1);
}

void Sound::FadeOut(int fadeOutTime)
{
	Mix_FadeOutChannel(-1, fadeOutTime);
}

void Sound::FadeIn(int numOfLoops, int fadeInTime)
{
	Mix_FadeInChannel(-1, mSoundEffect, numOfLoops, fadeInTime);
}
