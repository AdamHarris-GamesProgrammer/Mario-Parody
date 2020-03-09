#pragma once
#include "SDL_mixer.h"
#include <iostream>

class Music
{
public:
	Music();
	~Music();

	void Load(std::string filePath);
	void Play(int numOfLoops = -1);
	void Stop();
	void Pause();
	void Resume();
	void FadeIn(int numOfLoops, int fadeInTime);
	void FadeOut(int fadeOutTime);

	int GetVolume() { return mVolume; }
	void SetVolume(int newValue) {
		if (newValue <= MIX_MAX_VOLUME) { mVolume = newValue; }
		else { mVolume = MIX_MAX_VOLUME; }
		Mix_VolumeMusic(mVolume);
	}

	bool IsPlaying() const { return Mix_PlayingMusic(); }

private:
	Mix_Music* mMusic;
	int mVolume;
};

