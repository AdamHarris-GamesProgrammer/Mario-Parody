#pragma once
#include "SDL_mixer.h"
#include <iostream>

class Music
{
public:
	Music();
	~Music();

	//Loads the music
	void Load(std::string filePath);

	//Plays the music
	void Play(int numOfLoops = -1);

	//Stops the music
	void Stop();

	//Pauses the music
	void Pause();

	//Resumes the music
	void Resume();

	//Fades the music in and out 
	void FadeIn(int numOfLoops, int fadeInTime);
	void FadeOut(int fadeOutTime);

	//Getter/Setters for volume control
	int GetVolume() { return mVolume; }
	void SetVolume(int newValue) {
		if (newValue <= MIX_MAX_VOLUME) { mVolume = newValue; }
		else { mVolume = MIX_MAX_VOLUME; }
		Mix_VolumeMusic(mVolume);
	}

	//returns true if the music is playing
	bool IsPlaying() const { return Mix_PlayingMusic(); }

private:
	Mix_Music* mMusic;
	int mVolume;
};

