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

	float newYPos = GetPosition().y;
	float newXPos = GetPosition().x;

	if (mPlayerVelX != 0) {
		newXPos += mPlayerVelX * mMovementSpeed * deltaTime;
	}

	if (!bGrounded) {
		newYPos += GRAVITY * deltaTime;
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
	int rightTile = (newXPos + csc->GetTexWidth() - 2) / TILE_WIDTH;
	int topTile = newYPos / TILE_HEIGHT;
	int bottomTile = (newYPos + csc->GetTexHeight() - 2) / TILE_HEIGHT;

	//std::cout << "Left Tile: " << leftTile << " Right Tile: " << rightTile << " Top Tile: " << topTile << " Bottom Tile: " << bottomTile << std::endl;

	if (!bJumping) {
		//for (int y = topTile; y <= bottomTile; ++y) {
		//	for (int x = leftTile; x <= rightTile; ++x) {
		//		std::cout << "X: " << x << " Y: " << y << std::endl;
		//		int tileCollisionType = GetGame()->GetMap()->GetValueAtTile(y, x);
		//		if (tileCollisionType == 0) {
		//			std::cout << "Collision" << std::endl;
		//			newXPos = GetPosition().x;
		//			newYPos = GetPosition().y;
		//		}	
		//	}
		//}
		
		if (GetGame()->GetMap()->GetValueAtTile(bottomTile, leftTile) == 0) {
			std::cout << "Bottom" << std::endl;
			newYPos = GetPosition().y;
		}

	}
	else
	{
		//top
		if (GetGame()->GetMap()->GetValueAtTile(topTile, leftTile) == 0) {
			std::cout << "Top" << std::endl;
			mJumpForce = 0.0f;
			
		}
	}

	if (GetGame()->GetMap()->GetValueAtTile(bottomTile, leftTile) == 0) {
		std::cout << "Left" << std::endl;
		newXPos = GetPosition().x;
	}
	if (GetGame()->GetMap()->GetValueAtTile(bottomTile, rightTile) == 0) {
		std::cout << "Right" << std::endl;
		newXPos = GetPosition().x;
	}

	int playerFootTile = 0;
	if (bJumping) {
		std::cout << "Jumping" << std::endl;
		playerFootTile = GetGame()->GetMap()->GetValueAtTile(bottomTile + 1, leftTile);
	}
	else
	{
		playerFootTile = GetGame()->GetMap()->GetValueAtTile(bottomTile, leftTile);
	}
	
	if (playerFootTile != 0 && playerFootTile != 32) {
		bGrounded = false;
	}
	else
	{
		bGrounded = true;
	}

	if (newXPos < 0.0f || (newXPos + csc->GetTexWidth()) >= GetGame()->GetMap()->GetCalculatedLevelWidth()) {
		newXPos = GetPosition().x;
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
	mPlayerVelY = 0.0f;

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
				mPlayerVelY = -1.0f;
			}
		}
	}
}

void Mario::ChangePlayerTile(Vector2 position)
{
	GetGame()->GetMap()->ChangeTileAt(position.y / TILE_HEIGHT, position.x / TILE_WIDTH, -1);
}

