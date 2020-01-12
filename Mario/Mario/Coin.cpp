#include "Coin.h"
#include "AnimSpriteComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "MovementComponent.h"

Coin::Coin(class Game* game) : Actor(game) {
	AnimSpriteComponent* asc = new  AnimSpriteComponent(this);

	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Characters/Coins/Coin01.png", true),
		game->GetTexture("Assets/Characters/Coins/Coin02.png", true)
	};

	asc->SetAnimTextures(anims);
	asc->SetAnimFPS(2);


	mCircle = new CircleComponent(this);
	mCircle->SetRadius(18.0f);

	MovementComponent* mc = new MovementComponent(this);
	mc->SetForwardSpeed(1200.0f);
}

Coin::~Coin() {
	GetGame()->RemoveCoin(this);
}


