#include "Coin.h"
#include "CircleComponent.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "GameScreen.h"

Coin::Coin(class Game* game, SDL_Rect* srcRect, SDL_Rect* destRect) : Tile(game, srcRect, destRect, 2) { //sets up base values
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(18.0f);

}

Coin::~Coin() {
	//cleans up memory
	delete mCircle;
	mCircle = NULL;

	//deletes coin from the current screen
	mGame->GetCurrentScreen()->RemoveCoin(this);
}

void Coin::Update(float deltaTime)
{
	Tile::Update(deltaTime);

	//Animates the button
	mSrcRect->x = currentFrame * TILE_WIDTH;

	//gets the current time
	currentElapsedTime += deltaTime;

	if (currentElapsedTime > deltaTime * 10) { //if the current elapsed time is greater than (roughly) 160ms
		//increment frame counter
		currentFrame++;
		currentElapsedTime = 0;
	}

	//Resets the frame to 0 once it goes through all coin animations
	if (currentFrame > 9) {
		currentFrame = 0;
	}
}

