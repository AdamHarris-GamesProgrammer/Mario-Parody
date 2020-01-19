#include "Mario.h"
#include "AnimSpriteComponent.h"
#include "CircleComponent.h"
#include "TileMapComponent.h"
#include "Game.h"
#include "Coin.h"

Mario::Mario(class Game* game): Actor(game), mMovementSpeed(0.0f), mJumpForce(0.0f), mJumping(false)
{
	asc = new AnimSpriteComponent(this);
	mGameCamera = mGame->GetCamera();

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
	mCanJump = true;

	mDestRect = new SDL_Rect();
	mDestRect->h = asc->GetTexHeight();
	mDestRect->w = asc->GetTexWidth();
	mDestRect->x = GetPosition().x;
	mDestRect->y = GetPosition().y;

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.0f);
}

void Mario::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	mGameCamera = mGame->GetCamera();

	position = GetPosition();

	if (mJumping) {
		position.y -= mJumpForce * deltaTime;

		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f) {
			mJumping = false;
		}
	}

	int centralXPosition = (int)((position.x) / TILE_WIDTH);
	int footPosition = (int)(position.y + asc->GetTexHeight() * 0.5f) / TILE_HEIGHT;

	int tileValue = GetGame()->GetMap()->GetValueAtTile(footPosition, centralXPosition);

	if (tileValue == -1) {
		AddGravity(deltaTime);
	}
	else
	{
		mCanJump = true;
	}

	position.x += mMovementSpeed * deltaTime;

	//32 = player width, 1024 = level width
	if ((position.x < 0) || (position.x + 32 > 1024)) {
		position.x -= mMovementSpeed * deltaTime;
	}
	//48 = player height, 640 = level height
	if ((position.y < 0) || (position.y + 48 > 640)) {
		position.y -= mMovementSpeed * deltaTime;
	}
	
	std::cout << position.x << std::endl;
	
	SetPosition(position);

	mDestRect->x = position.x;
	mDestRect->y = position.y;

	//checks to see if a coin has been picked up
	for (auto coin : GetGame()->GetCoins()) {
		if (Intersect(*mCircle, *(coin->GetCircle()))) {
			std::cout << "Collision" << std::endl;
			GetGame()->GetMap()->ChangeTileAt((coin->GetPosition().y / TILE_HEIGHT), (coin->GetPosition().x / TILE_WIDTH), -1);
			coin->SetState(EDead);

		}
	}

	SetCamera();

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

	if (state[SDL_SCANCODE_SPACE]) {
		if (mCanJump) {
			Jump();
		}
	}
}

void Mario::Draw()
{
	SDL_Rect* dest = mDestRect;

	dest->x -= mGameCamera->x;
	dest->y -= mGameCamera->y;
	asc->Draw(GetGame()->GetRenderer(), mSrcRect, dest, 0.0f, NULL, mFlipState);
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

void Mario::SetCamera()
{
	mGameCamera->x = (GetPosition().x + 16) - SCREEN_WIDTH / 2;
	mGameCamera->y = (GetPosition().y + 24) - SCREEN_HEIGHT / 2;

	if (mGameCamera->x < 0) {
		mGameCamera->x = 0;
	}
	if (mGameCamera->y < 0) {
		mGameCamera->y = 0;
	}
	//1024 level width, 640 level height
	if (mGameCamera->x > 1024 - mGameCamera->w) {
		mGameCamera->x = 1024 - mGameCamera->w;
	}
	if (mGameCamera->y > 640 - mGameCamera->h) {
		mGameCamera->y = 640 - mGameCamera->h;
	}
}
