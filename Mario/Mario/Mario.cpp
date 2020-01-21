#include "Mario.h"
#include "CircleComponent.h"
#include "TileMapComponent.h"
#include "CharacterSpriteComponent.h"
#include "Game.h"
#include "Coin.h"

Mario::Mario(class Game* game): Actor(game), mMovementSpeed(0.0f), mJumpForce(0.0f), mJumping(false)
{
	csc = new CharacterSpriteComponent(this);

	std::vector<SDL_Texture*> anims = {
		game->GetEngine()->GetTexture("Assets/Characters/Mario/Mario01.png", true),
		game->GetEngine()->GetTexture("Assets/Characters/Mario/Mario02.png", true),
		game->GetEngine()->GetTexture("Assets/Characters/Mario/Mario03.png", true)
	};
	csc->SetAnimTextures(anims);
	csc->SetAnimFPS(3);

	mCanJump = true;

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.0f);
}

void Mario::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);


	position = GetPosition();

	if (mJumping) {
		position.y -= mJumpForce * deltaTime;

		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f) {
			mJumping = false;
		}
	}

	position.x += mMovementSpeed * deltaTime;

	//32 = player width, 1024 = level width
	if ((position.x < 0) || (position.x + csc->GetTexWidth() > 1024)) {
		position.x -= mMovementSpeed * deltaTime;
	}
	//48 = player height, 640 = level height
	if ((position.y < 0) || (position.y + csc->GetTexHeight() > 640)) {
		position.y -= mMovementSpeed * deltaTime;
	}
	
	SetPosition(position);

	csc->GetDestRect()->x = position.x - GetGame()->mCamera.x;
	csc->GetDestRect()->y = position.y;

	int centralXPosition = (int)((position.x + csc->GetTexWidth()) / TILE_WIDTH);

	int footPosition = (int)(position.y + csc->GetTexHeight()) / TILE_HEIGHT;

	std::cout << "X Position: " << position.x << " Central X Position: " << centralXPosition << std::endl;
	std::cout << "Y Position: " << position.y <<  std::endl;

	int tileValue = GetGame()->GetMap()->GetValueAtTile(footPosition, centralXPosition);

	if (tileValue == -1 || tileValue == 1) {
		AddGravity(deltaTime);
	}
	else
	{
		mCanJump = true;
	}

	//checks to see if a coin has been picked up
	for (auto coin : GetGame()->GetCoins()) {
		if (Intersect(*mCircle, *(coin->GetCircle()))) {
			std::cout << "Collision" << std::endl;
			GetGame()->GetMap()->ChangeTileAt((coin->GetPosition().y / TILE_HEIGHT), (coin->GetPosition().x / TILE_WIDTH), -1);
			coin->SetState(EDead);
		}
	}
}

void Mario::HandleEvents(const uint8_t* state)
{
	mMovementSpeed = 0.0f;

	if (state[SDL_SCANCODE_A]) {
		mMovementSpeed -= 100.0f;
		csc->SetRendererFlip(SDL_FLIP_HORIZONTAL);
	}
	else if (state[SDL_SCANCODE_D]) {
		mMovementSpeed += 100.0f;
		csc->SetRendererFlip(SDL_FLIP_NONE);
	}

	if (state[SDL_SCANCODE_SPACE]) {
		if (mCanJump) {
			Jump();
		}
	}
}

void Mario::CancelJump()
{
	mJumpForce = 0;
}

void Mario::Jump()
{
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Mario::AddGravity(float deltaTime)
{
	SetPosition(Vector2(position.x, position.y += GRAVITY * deltaTime));

	mCanJump = false;
}

