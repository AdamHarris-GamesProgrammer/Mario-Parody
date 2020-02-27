#include "Koopa.h"
#include "CharacterSpriteComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "TileMapComponent.h"
#include "TileValues.h"

Koopa::Koopa(class Game* game) : Actor(game)
{
	csc = new CharacterSpriteComponent(this, 110, 32, 30);
	
	walkingAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Koopa/Koopa01.png"));
	
	
	flippedAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Koopa/KoopaFlipped01.png"));

	csc->SetAnimTextures(walkingAnims);
	csc->SetAnimFPS(1);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(8.0f);


	flippedTimer = flippedDuration;
}

Koopa::~Koopa()
{

}

void Koopa::UpdateActor(float deltaTime)
{
	Vector2 newPosition = GetPosition();
	if (bAlive) {
		if (!bFlipped) {

			int leftTile = newPosition.x / TILE_WIDTH;
			int rightTile = (newPosition.x + csc->GetTexWidth()) / TILE_WIDTH;
			int topTile = newPosition.y / TILE_HEIGHT;
			int bottomTile = (newPosition.y + csc->GetTexHeight()) / TILE_HEIGHT;

			int midLeftTile = GetGame()->GetMap()->GetValueAtTile(bottomTile - 1, leftTile);
			int midRightTile = GetGame()->GetMap()->GetValueAtTile(bottomTile - 1, rightTile);

			if (bMovingRight) {
				newPosition.x += mMovementSpeed * deltaTime;

				//checks right tile collision
				if (midRightTile == BRICK || midRightTile == KOOPATURN) {
					newPosition.x = GetPosition().x;
					bMovingRight = false;
				}

				if (GetGame()->GetMap()->GetValueAtTile(bottomTile, rightTile) == AIR) {
					bMovingRight = false;
				}

			}
			else
			{
				newPosition.x -= mMovementSpeed * deltaTime;

				if (midLeftTile == BRICK || midLeftTile == KOOPATURN) {
					newPosition.x = GetPosition().x;
					bMovingRight = true;
				}

				if (GetGame()->GetMap()->GetValueAtTile(bottomTile, leftTile) == AIR) {
					bMovingRight = true;
				}
				
			}

			//restrict X Position to screen bounds
			if (newPosition.x < 0.0f || (newPosition.x + csc->GetTexWidth()) >= GetGame()->GetMap()->GetCalculatedLevelWidth()) {
				newPosition.x = GetPosition().x;
				bMovingRight = !bMovingRight;
			}


			//orient sprite
			if (bMovingRight) {
				csc->SetRendererFlip(SDL_FLIP_NONE);
			}
			else
			{
				csc->SetRendererFlip(SDL_FLIP_HORIZONTAL);
			}


		}
		else
		{
			csc->SetAnimTextures(flippedAnims);
			flippedTimer -= deltaTime;

			if (flippedTimer <= 0) {
				bFlipped = false;
				csc->SetAnimTextures(walkingAnims);
				flippedTimer = 3.0f;
			}

		}

		SetPosition(newPosition);
		csc->GetDestRect()->x = GetPosition().x - GetGame()->mCamera.x;
		csc->GetDestRect()->y = GetPosition().y;
	}
	else {
		mGame->RemoveKoopa(this);
		delete this;
	}
	
}
