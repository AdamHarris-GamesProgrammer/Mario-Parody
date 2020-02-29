#include "Coin.h"
#include "CircleComponent.h"
#include "Game.h"

Coin::Coin(class Game* game, SDL_Rect* srcRect, SDL_Rect* destRect) : Tile(game, srcRect, destRect, 2, false) {
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(18.0f);
}

Coin::~Coin() {
	GetGame()->RemoveCoin(this);
}


