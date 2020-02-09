#include "Mario.h"
#include "CircleComponent.h"
#include "CollisionComponent.h"
#include "TileMapComponent.h"
#include "CharacterSpriteComponent.h"
#include "Game.h"
#include "Coin.h"
#include "Tile.h"

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
	mPlayerVelY = 0.0f;

	bCanJump = true;
}

void Mario::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	//Vertical Movements
	float newYPos = GetPosition().y;
	float newXPos = GetPosition().x;

	if (!bCanJump && newYPos <= 416.0f) {
		newYPos += GRAVITY * deltaTime;
	}

	if (bJumping) {
		newYPos -= mJumpForce * deltaTime;

		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f) {
			bJumping = false;
		}
	}

	//moving up
	if (mPlayerVelY < 0) {
		Tile* upTile = GetGame()->GetMap()->GetTile((newYPos / TILE_HEIGHT - 1), (newXPos / TILE_WIDTH));
		if (upTile != nullptr) {
			std::cout << "Up Tile X: " << upTile->GetPosition().x << " Y: " << upTile->GetPosition().y << std::endl;
			if (upTile->GetTileType() != -1) {
				if (Intersect(csc->GetDestRect(), upTile->GetDestRect())) {
					newYPos = GetPosition().y;
				}
			}
		}
	}
	//moving down
	else if (mPlayerVelY > 0) {
		Tile* downTile = GetGame()->GetMap()->GetTile((newYPos / TILE_HEIGHT + 1), (newXPos / TILE_WIDTH));
		if (downTile != nullptr) {
			std::cout << "Down Tile X: " << downTile->GetPosition().x << " Y: " << downTile->GetPosition().y << std::endl;
			if (downTile->GetTileType() != -1) {
				if (Intersect(csc->GetDestRect(), downTile->GetDestRect())) {
					newYPos = GetPosition().y;
				}
			}
		}
	}

	//Horizontal Movements
	if (mPlayerVelX != 0)
	{
		newXPos += mPlayerVelX * mMovementSpeed * deltaTime;
	}

	//moving left
	if (mPlayerVelX < 0) {
		Tile* leftTile = GetGame()->GetMap()->GetTile((newYPos / TILE_HEIGHT), (newXPos / TILE_WIDTH));
		if (leftTile != nullptr) {
			std::cout << "Left Tile X: " << leftTile->GetPosition().x << " Y: " << leftTile->GetPosition().y << std::endl;
			if (leftTile->GetTileType() != -1) {
				if (Intersect(csc->GetDestRect(), leftTile->GetDestRect())) {
					newXPos = GetPosition().x;
				}
			}
		}

	}
	//moving right
	else if (mPlayerVelX > 0) {
		Tile* rightTile = GetGame()->GetMap()->GetTile((newYPos / TILE_HEIGHT), (newXPos / TILE_WIDTH + 1));
		if (rightTile != nullptr) {
			std::cout << "Right Tile X: " << rightTile->GetPosition().x << " Y: " << rightTile->GetPosition().y << std::endl;
			if (rightTile->GetTileType() != -1) {
				if (Intersect(csc->GetDestRect(), rightTile->GetDestRect())) {
					newXPos = GetPosition().x;
				}
			}
		}
	}

	SetPosition(Vector2(newXPos, newYPos));

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
			if (!bJumping) {
				mJumpForce = INITIAL_JUMP_FORCE;
				bJumping = true;
				bCanJump = false;
				mPlayerVelY = -1.0f;
			}
		}
	}
}

