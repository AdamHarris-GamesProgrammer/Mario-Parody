#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>

class Sound
{
public:
	Sound(bool loop = false);
	~Sound();

	void Load(std::string filePath);
	void Play();
	void Pause();
	void Resume();
	void FadeOut(int fadeOutTime);
	void FadeIn(int numOfLoops, int fadeInTime);

	int GetVolume() { return mVolume; }
	void SetVolume(int newValue) {
		if (newValue <= MIX_MAX_VOLUME) { mVolume = newValue; }
		else { mVolume = MIX_MAX_VOLUME; }
		Mix_VolumeChunk(mSoundEffect, mVolume);
	}

private:
	Mix_Chunk* mSoundEffect;
	bool mLooping = false;

	int mVolume;
};

