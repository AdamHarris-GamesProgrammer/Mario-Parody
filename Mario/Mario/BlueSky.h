#pragma once


class BlueSky
{
public:
	BlueSky();
	~BlueSky();

	bool Initialize();

	void Shutdown();

	void RunLoop();

private:


protected:
	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;
};

