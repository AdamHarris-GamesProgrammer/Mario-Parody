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

	if (!bGrounded) {
		newYPos += GRAVITY * deltaTime;
	}

	if (bJumping) {
		newYPos -= mJumpForce * deltaTime;

		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f) {
			bJumping = false;
		}
	}

	////moving up
	//if (newYPos < GetPosition().y) {
	//	Tile* upTile = GetGame()->GetMap()->GetTile((newYPos / TILE_HEIGHT - 1), (newXPos / TILE_WIDTH));
	//	if (upTile != nullptr) {
	//		//std::cout << "Up Tile X: " << upTile->GetPosition().x << " Y: " << upTile->GetPosition().y << std::endl;
	//		if (upTile->GetTileType() == 0) {
	//			if (Intersect(csc->GetDestRect(), upTile->GetDestRect())) {
	//				newYPos = GetPosition().y;
	//				//bCanJump = true;
	//				bGrounded = false;
	//				std::cout << "Up tile Collision" << std::endl;
	//			}
	//		}
	//	}
	//}
	////moving down
	//else if (newYPos > GetPosition().y) {
	//	Tile* downTile = GetGame()->GetMap()->GetTile((newYPos / TILE_HEIGHT + 1), (newXPos / TILE_WIDTH));
	//	if (downTile != nullptr) {
	//		//std::cout << "Down Tile X: " << downTile->GetPosition().x << " Y: " << downTile->GetPosition().y << std::endl;
	//		if (downTile->GetTileType() == 0) {
	//			if (Intersect(csc->GetDestRect(), downTile->GetDestRect())) {
	//				newYPos = GetPosition().y;
	//				bCanJump = true;
	//				bJumping = false;
	//				bGrounded = true;
	//				std::cout << "Down tile collision" << std::endl;
	//			}
	//		}
	//	}
	//}

	Tile* upTile = GetGame()->GetMap()->GetTile((newYPos / TILE_HEIGHT), (newXPos / TILE_WIDTH));
	if (upTile != nullptr) {
		std::cout << "Up Tile X: " << upTile->GetPosition().x << " Y: " << upTile->GetPosition().y << upTile->GetTileType() << std::endl;
		if (upTile->GetTileType() == 0) {
			if (Intersect(csc->GetDestRect(), upTile->GetDestRect())) {
				newYPos = GetPosition().y;
				//bCanJump = true;
				bGrounded = false;

				std::cout << "Up tile Collision" << std::endl;
			}
		}
	}
	Tile* downTile = GetGame()->GetMap()->GetTile((newYPos / TILE_HEIGHT + 1), (newXPos / TILE_WIDTH));
	if (downTile != nullptr) {
		std::cout << "Down Tile X: " << downTile->GetPosition().x << " Y: " << downTile->GetPosition().y << downTile->GetTileType() << std::endl;
		if (downTile->GetTileType() == 0) {
			if (Intersect(csc->GetDestRect(), downTile->GetDestRect())) {
				newYPos = GetPosition().y;
				bJumping = false;

				std::cout << "Down tile collision" << std::endl;
			}
		}
	}

	if (downTile->GetTileType() == 0) {
		if (Intersect(csc->GetDestRect(), downTile->GetDestRect())) {
			newYPos = GetPosition().y;
			bGrounded = true;
			std::cout << "Down tile collision" << std::endl;
		}
	}

	if (!bJumping) {
		bCanJump = true;
		bGrounded = true;
	}
	if (bJumping) {
		bGrounded = false;
	}

	std::cout << "bCanJump: " << bCanJump << std::endl << "bJumping: " << bJumping << std::endl << "bGrounded: " << bGrounded << std::endl;

	//Horizontal Movements
	if (mPlayerVelX != 0)
	{
		newXPos += mPlayerVelX * mMovementSpeed * deltaTime;
	}

	//moving left
	if (mPlayerVelX < 0) {
		Tile* leftTile = GetGame()->GetMap()->GetTile((newYPos / TILE_HEIGHT), (newXPos / TILE_WIDTH));
		if (leftTile != nullptr) {
			if (leftTile->GetTileType() == 0) {
				if (Intersect(csc->GetDestRect(), leftTile->GetDestRect())) {
					newXPos = GetPosition().x;

					std::cout << "Left tile collision" << std::endl;
				}
			}
		}

	}
	//moving right
	else if (mPlayerVelX > 0) {
		Tile* rightTile = GetGame()->GetMap()->GetTile((newYPos / TILE_HEIGHT), (newXPos / TILE_WIDTH + 1));
		if (rightTile != nullptr) {
			if (rightTile->GetTileType() == 0) {
				if (Intersect(csc->GetDestRect(), rightTile->GetDestRect())) {
					newXPos = GetPosition().x;

					std::cout << "Right tile collision" << std::endl;
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
			if (!bJumping && bCanJump) {
				mJumpForce = INITIAL_JUMP_FORCE;
				bJumping = true;
				bCanJump = false;
				mPlayerVelY = -1.0f;
			}
		}
	}
}

