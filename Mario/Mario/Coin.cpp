#include "Coin.h"
#include "CircleComponent.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "GameScreen.h"

Coin::Coin(class Game* game, SDL_Rect* srcRect, SDL_Rect* destRect) : Tile(game, srcRect, destRect, 2) {
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(18.0f);
}

Coin::~Coin() {
	delete mCircle;
	mCircle = NULL;
	mGame->GetCurrentScreen()->RemoveCoin(this);
}

void Coin::Update(float deltaTime)
{
	Tile::Update(deltaTime);

	mSrcRect->x += TILE_WIDTH;
	if (mSrcRect->x > 319) {
		mSrcRect->x = 0;
	}
	
}

