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
}

void Mario::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	float newXPos = 0.0f;
	float newYPos = 0.0f;

	//GRAVITY
	mPlayerVelY += GRAVITY * deltaTime;

	if (mPlayerVelX > 10.0f) {
		mPlayerVelX = 10.0f;
	}
	if (mPlayerVelX < -10.0f) {
		mPlayerVelX = -10.0f;
	}
	if (mPlayerVelY > 100.0f) {
		mPlayerVelY = 100.0f;
	}
	if (mPlayerVelY < -500.0f) {
		mPlayerVelY = -500.0f;
	}
	

	 newXPos = GetPosition().x + mPlayerVelX * deltaTime;
	 newYPos = GetPosition().y + mPlayerVelY * deltaTime;

	 if ((newXPos + csc->GetTexWidth() > 1024)) {
		 std::cout << newXPos + csc->GetTexWidth() << std::endl;
		 newXPos = 1024 - csc->GetTexWidth();
	 }
	 else if(newXPos < 0) {
		 newXPos = 0;
	 }

	if (mPlayerVelX < 0) { //move left
		if (GetGame()->GetMap()->GetValueAtTile(newYPos / TILE_HEIGHT, newXPos / TILE_WIDTH) != 0 || GetGame()->GetMap()->GetValueAtTile((newYPos + 28) / TILE_HEIGHT, newXPos / TILE_WIDTH) != 0) {
			newXPos = (int)newXPos - 1;
			mPlayerVelX = 0.0f;
		}
	}
	else if(mPlayerVelX > 0){ //move right
		if (GetGame()->GetMap()->GetValueAtTile(newYPos / TILE_HEIGHT, (newXPos) / TILE_WIDTH) != 0 || GetGame()->GetMap()->GetValueAtTile((newYPos + 28) / TILE_HEIGHT, newXPos / TILE_WIDTH) != 0) {
			newXPos = (int)newXPos + 1;
			mPlayerVelX = 0.0f;
		}
	}
	bGrounded = false;
	if (mPlayerVelY <= 0) { //moving up
		if (GetGame()->GetMap()->GetValueAtTile(newYPos + 32/ TILE_HEIGHT, newXPos / TILE_WIDTH) != 0) {
			newYPos = (int)newYPos + 1;
			mPlayerVelY = 0.0f;
		}
	}
	else { //moving down
		if (GetGame()->GetMap()->GetValueAtTile((newYPos + 32) / TILE_HEIGHT, newXPos / TILE_WIDTH) == 0) {
			newYPos = (int)newYPos;
			mPlayerVelY = 0.0f;
			bGrounded = true;
		}
	}

	printf("X Position: %f, Y Position: %f\t", GetPosition().x, GetPosition().y);
	printf("X Velocity: %f, Y Velocity: %f\n", mPlayerVelX, mPlayerVelY);

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

	for (auto goal : GetGame()->GetLevelGoal()) {
		if (Intersect(*csc->GetDestRect(), *goal->GetDestRect())) {
			//TODO: Implement next level logic 
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
			if (mPlayerVelY == 0.0f) {
				mPlayerVelY = -5000.0f;
			}
		}

	}
}

