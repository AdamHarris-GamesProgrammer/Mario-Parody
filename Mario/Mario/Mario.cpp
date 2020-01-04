#include "Mario.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Mario::Mario(class Game* game): Actor(game), mMovementSpeed(0.0f)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);

	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Characters/Mario/Mario01.png", true)
	};
	asc->SetAnimTextures(anims);
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
		mMovementSpeed -= 250.0f;
	}
	else if (state[SDL_SCANCODE_D]) {
		mMovementSpeed += 250.0f;
	}
	else {
		
	}
}
