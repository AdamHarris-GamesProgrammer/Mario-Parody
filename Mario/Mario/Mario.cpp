#include "Mario.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Mario::Mario(class Game* game): Actor(game), mMovementSpeed(0.0f)
{
	asc = new AnimSpriteComponent(this);

	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Characters/Mario/Mario01.png", true),
		game->GetTexture("Assets/Characters/Mario/Mario02.png", true),
		game->GetTexture("Assets/Characters/Mario/Mario03.png", true)
	};
	asc->SetAnimTextures(anims);
	asc->SetAnimFPS(3);

	mSrcRect = new SDL_Rect();
	mSrcRect->x = 0;
	mSrcRect->y = 0;
	mSrcRect->w = asc->GetTexWidth();
	mSrcRect->h = asc->GetTexHeight();

	mFlipState = SDL_FLIP_NONE;
}

void Mario::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector2 pos = GetPosition();

	pos.x += mMovementSpeed * deltaTime;

	SetPosition(pos);
}

void Mario::HandleEvents(const uint8_t* state)
{
	mMovementSpeed = 0.0f;

	if (state[SDL_SCANCODE_A]) {
		mMovementSpeed -= 100.0f;
		mFlipState = SDL_FLIP_HORIZONTAL;
		
	}
	else if (state[SDL_SCANCODE_D]) {
		mMovementSpeed += 100.0f;
		mFlipState = SDL_FLIP_NONE;
		
	}
	else {
		
	}
}

void Mario::Draw()
{
	asc->Draw(GetGame()->GetRenderer(), mSrcRect, 0.0f, NULL, mFlipState);
}
