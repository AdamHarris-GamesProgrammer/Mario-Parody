#include "Mario.h"
#include "CircleComponent.h"
#include "CollisionComponent.h"
#include "TileMapComponent.h"
#include "CharacterSpriteComponent.h"
#include "Game.h"
#include "Coin.h"
#include "Tile.h"
#include "TileValues.h"
#include "Koopa.h"



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

	if (!bDead) {
		Vector2 newPosition = GetPosition();

		if (mPlayerVelX != 0) {
			newPosition.x += mPlayerVelX * mMovementSpeed * deltaTime;
		}

		if (bJumping) {
			Jump(newPosition, deltaTime);
		}

		int leftTile = newPosition.x / TILE_WIDTH;
		int rightTile = (newPosition.x + csc->GetTexWidth()) / TILE_WIDTH;
		int topTile = newPosition.y / TILE_HEIGHT;
		int bottomTile = (newPosition.y + csc->GetTexHeight()) / TILE_HEIGHT;

		int topLeftTile = GetGame()->GetMap()->GetValueAtTile(topTile, leftTile);
		int topRightTile = GetGame()->GetMap()->GetValueAtTile(topTile, rightTile);
		int midLeftTile = GetGame()->GetMap()->GetValueAtTile(bottomTile - 1, leftTile);
		int midRightTile = GetGame()->GetMap()->GetValueAtTile(bottomTile - 1, rightTile);
		int bottomLeftTile = GetGame()->GetMap()->GetValueAtTile(bottomTile, leftTile);
		int bottomRightTile = GetGame()->GetMap()->GetValueAtTile(bottomTile, rightTile);

		//Top Collisions
		if ((topLeftTile != AIR && topLeftTile != COIN && topLeftTile != KOOPATURN) || (topRightTile != AIR && topRightTile != COIN && topRightTile != KOOPATURN)) {
			newPosition.y = GetPosition().y;
			mJumpForce = 0.0f;
		}

		if (topLeftTile == GOLDBRICK || topRightTile == GOLDBRICK) {
			//TODO: SCREENSHAKE, Take health away from pow block
			for (auto enemy : mGame->GetKoopas()) {
				enemy->SetFlipped(true);
			}
		}

		//Mid Collisions
		if (midLeftTile == BRICK || midRightTile == BRICK) {
			newPosition.x = GetPosition().x;
		}

		//Bottom collisions
		if ((bottomRightTile == AIR && bottomLeftTile == AIR) || (bottomRightTile == DROPBRICK && bottomLeftTile == DROPBRICK) || (bottomRightTile == KOOPATURN && bottomLeftTile == KOOPATURN)) {
			bGrounded = false;
			newPosition.y += GRAVITY * deltaTime;
		}
		else
		{
			bCanJump = true;
			bGrounded = true;
		}

		//constrains player to X level bounds
		if (newPosition.x < 0.0f || (newPosition.x + csc->GetTexWidth()) >= GetGame()->GetMap()->GetCalculatedLevelWidth()) {
			newPosition.x = GetPosition().x;
		}

		//Sets the players position and dest rect to work with the camera system
		SetPlayerPosition(newPosition);
		//checks for collision with coins, enemies and level goals
		CollisionChecks();
	}
	else
	{
		//player falls off screen
		Vector2 newPosition = GetPosition();
		newPosition.y += GRAVITY * deltaTime;
		SetPlayerPosition(newPosition);
	}
	
}

void Mario::HandleEvents(const uint8_t* state)
{
	mPlayerVelX = 0.0f;

	if (!bDead) {
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

}

void Mario::ChangePlayerTile(Vector2 position)
{
	GetGame()->GetMap()->ChangeTileAt(position.y / TILE_HEIGHT, position.x / TILE_WIDTH, -1);
}

void Mario::SetPlayerPosition(const Vector2& newValue)
{
	Actor::SetPosition(newValue);
	csc->GetDestRect()->x = GetPosition().x - GetGame()->mCamera.x;
	csc->GetDestRect()->y = GetPosition().y;
}

void Mario::CollisionChecks()
{
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

	for (auto enemy : GetGame()->GetKoopas()) {
		if (enemy != nullptr) {
			if (Intersect(*mCircle, *(enemy->GetCircle()))) {
				//TODO setup koopa active check
				if (enemy->GetFlipped()) {
					enemy->SetAlive(false);
				}
				else
				{
					bDead = true;
				}
			}
		}
	}
}

void Mario::Jump(Vector2& newPos, float deltaTime)
{
	newPos.y -= mJumpForce * deltaTime;

	mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

	if (mJumpForce <= 0.0f) {
		bJumping = false;
		bCanJump = true;
		mJumpForce = 0.0f;
	}
}

