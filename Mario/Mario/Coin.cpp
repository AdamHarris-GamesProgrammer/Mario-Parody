#include "Coin.h"
#include "CircleComponent.h"
#include "Game.h"
#include "GameScreen.h"

Coin::Coin(class Game* game, SDL_Rect* srcRect, SDL_Rect* destRect) : Tile(game, srcRect, destRect, 2) {
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(18.0f);
}

Coin::~Coin() {
	mGame->GetCurrentScreen->RemoveCoin(this);
	delete mCircle;
	mCircle = NULL;
}


