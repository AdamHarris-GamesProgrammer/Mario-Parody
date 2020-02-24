#include "Mario.h"
#include "CircleComponent.h"
#include "CollisionComponent.h"
#include "TileMapComponent.h"
#include "CharacterSpriteComponent.h"
#include "Game.h"
#include "Coin.h"
#include "Tile.h"
#include "TileValues.h"



Mario::Mario(class Game* game) : Actor(game)
{
	csc = new CharacterSpriteComponent(this);

	std::vector<SDL_Texture*> anims = {
		game->GetEngine()->GetTexture("Assets/Characters/Mario/MarioTest.png", true)
	};
	csc->SetAnimTextures(anims);
	csc->SetAnimFPS(3);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.0f);

	mPlayerVelX = 0.0f;

	bCanJump = true;
}

void Mario::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	float newYPos = GetPosition().y;
	float newXPos = GetPosition().x;

	if (mPlayerVelX != 0) {
		newXPos += mPlayerVelX * mMovementSpeed * deltaTime;
	}

	if (bJumping) {
		newYPos -= mJumpForce * deltaTime;

		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f) {
			bJumping = false;
			bCanJump = true;
			mJumpForce = 0.0f;
		}
	}

	int leftTile = newXPos / TILE_WIDTH;
	int rightTile = (newXPos + csc->GetTexWidth()) / TILE_WIDTH;
	int topTile = newYPos / TILE_HEIGHT;
	int bottomTile = (newYPos + csc->GetTexHeight()) / TILE_HEIGHT;
	

	int topLeftTile = GetGame()->GetMap()->GetValueAtTile(topTile, leftTile);
	int topRightTile = GetGame()->GetMap()->GetValueAtTile(topTile, rightTile);
	int midLeftTile = GetGame()->GetMap()->GetValueAtTile(bottomTile - 1, leftTile);
	int midRightTile = GetGame()->GetMap()->GetValueAtTile(bottomTile - 1, rightTile);
	int bottomLeftTile = GetGame()->GetMap()->GetValueAtTile(bottomTile, leftTile);
	int bottomRightTile = GetGame()->GetMap()->GetValueAtTile(bottomTile, rightTile);

	//Top Collisions
	if ((topLeftTile != AIR && topLeftTile != COIN) || (topRightTile != AIR && topRightTile != COIN)) {
		newYPos = GetPosition().y;
		mJumpForce = 0.0f;
	}

	//Mid Collisions
	if (midLeftTile == BRICK || midRightTile == BRICK) {
		newXPos = GetPosition().x;
	}
	
	//Bottom collisions
	if ((bottomRightTile == AIR && bottomLeftTile == AIR) || (bottomRightTile == DROPBRICK && bottomLeftTile == DROPBRICK)) {
		bGrounded = false;
		newYPos += GRAVITY * deltaTime;
	}
	else
	{
		bCanJump = true;
		bGrounded = true;
	}

	//constrains player to X level bounds
	if (newXPos < 0.0f || (newXPos + csc->GetTexWidth()) >= GetGame()->GetMap()->GetCalculatedLevelWidth()) {
		newXPos = GetPosition().x;
	}


	SetPosition(Vector2(newXPos, newYPos));

	//controls the players screen position related to the camera position
	csc->GetDestRect()->x = GetPosition().x - GetGame()->mCamera.x;
	csc->GetDestRect()->y = GetPosition().y;

	//checks to see if a coin has been picked up
	for (auto coin : GetGame()->GetCoins()) {
		if (Intersect(*mCircle, *(coin->GetCircle()))) {
			GetGame()->GetMap()->ChangeTileAt((coin->GetPosition().y / TILE_HEIGHT), (coin->GetPosition().x / TILE_WIDTH), -1);
			coin->SetState(EDead);
			mGame->IncrementScore();
		}
	}

	//checks to see if the player is colliding with the level goal
	if (GetGame()->GetLevelGoal() != nullptr) {
		if (Intersect(*csc->GetDestRect(), *(GetGame()->GetLevelGoal()->GetDestRect()))) {
			GetGame()->NextLevel();
		}
	}
}

void Mario::HandleEvents(const uint8_t* state)
{
	mPlayerVelX = 0.0f;

	if (state[SDL_SCANCODE_A]) {
		csc->SetRendererFlip(SDL_FLIP_HORIZONTAL);
		mPlayerVelX += -25.0f;
	}
	else if (state[SDL_SCANCODE_D]) {
		csc->SetRendererFlip(SDL_FLIP_NONE);
		mPlayerVelX += 25.0f;
	}

	if (state[SDL_SCANCODE_SPACE]) {
		if (bGrounded) {
			if (!bJumping && bCanJump) {
				mJumpForce = INITIAL_JUMP_FORCE;
				bGrounded = false;
				bJumping = true;
				bCanJump = false;
			}
		}
	}
}

void Mario::ChangePlayerTile(Vector2 position)
{
	GetGame()->GetMap()->ChangeTileAt(position.y / TILE_HEIGHT, position.x / TILE_WIDTH, -1);
}

