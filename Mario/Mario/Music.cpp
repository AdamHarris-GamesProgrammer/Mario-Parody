#include "Music.h"

Music::Music()
{
}

Music::~Music()
{
	Mix_FreeMusic(mMusic);
	mMusic = NULL;
}

void Music::Load(std::string filePath)
{
	mMusic = Mix_LoadMUS(filePath.c_str());
	if (!mMusic) {
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void Music::Play(int numOfLoops /*= 1*/)
{
	Mix_PlayMusic(mMusic, numOfLoops);
}

void Music::Stop()
{
	Mix_HaltMusic();
}

void Music::Pause()
{
	Mix_PauseMusic();
}

void Music::Resume()
{
	Mix_ResumeMusic();
}

void Music::FadeIn(int numOfLoops, int fadeInTime)
{
	Mix_FadeInMusic(mMusic, numOfLoops, fadeInTime);
}

void Music::FadeOut(int fadeOutTime)
{
	Mix_FadeOutMusic(fadeOutTime);
}
