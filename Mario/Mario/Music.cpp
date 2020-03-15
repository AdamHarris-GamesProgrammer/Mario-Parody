#include "Music.h"

Music::Music()
{

}

Music::~Music()
{
	//deletes the music from memory
	Mix_FreeMusic(mMusic);
	mMusic = NULL;
}

void Music::Load(std::string filePath)
{
	//Loads the music into memory
	mMusic = Mix_LoadMUS(filePath.c_str());
	if (!mMusic) {
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void Music::Play(int numOfLoops)
{
	//Plays the music
	Mix_PlayMusic(mMusic, numOfLoops);
}

void Music::Stop()
{
	//Stops the music
	Mix_HaltMusic();
}

void Music::Pause()
{
	//Pauses music
	Mix_PauseMusic();
}

void Music::Resume()
{
	//Resumes music
	Mix_ResumeMusic();
}

void Music::FadeIn(int numOfLoops, int fadeInTime)
{
	//Fades music in
	Mix_FadeInMusic(mMusic, numOfLoops, fadeInTime);
}

void Music::FadeOut(int fadeOutTime)
{
	//Fades music out
	Mix_FadeOutMusic(fadeOutTime);
}
