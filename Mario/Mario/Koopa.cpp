#include "Koopa.h"
#include "CharacterSpriteComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "TileMapComponent.h"
#include "TileValues.h"

Koopa::Koopa(class Game* game) : Actor(game)
{
	csc = new CharacterSpriteComponent(this, 110, 32, 30);
	
	std::vector<SDL_Texture*> anims = {
		game->GetEngine()->GetTexture("Assets/Characters/Koopa/Koopa01.png")
	};
	csc->SetAnimTextures(anims);
	csc->SetAnimFPS(1);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(16.0f);

	std::cout << "Koopa spawned" << std::endl;
}

Koopa::~Koopa()
{

}

void Koopa::UpdateActor(float deltaTime)
{

	float newXPos = GetPosition().x;
	float newYPos = GetPosition().y;

	int leftTile = newXPos / TILE_WIDTH;
	int rightTile = (newXPos + csc->GetTexWidth()) / TILE_WIDTH;
	int topTile = newYPos / TILE_HEIGHT;
	int bottomTile = (newYPos + csc->GetTexHeight()) / TILE_HEIGHT;

	int midLeftTile = GetGame()->GetMap()->GetValueAtTile(bottomTile - 1, leftTile);
	int midRightTile = GetGame()->GetMap()->GetValueAtTile(bottomTile - 1, rightTile);

	if (bMovingRight) {
		newXPos += mMovementSpeed * deltaTime;

		//checks right tile collision
		if (midRightTile == BRICK || midRightTile == KOOPATURN) {
			newXPos = GetPosition().x;
			bMovingRight = false;
		}

	}
	else
	{
		newXPos -= mMovementSpeed * deltaTime;

		if (midLeftTile == BRICK || midLeftTile == KOOPATURN) {
			newXPos = GetPosition().x;
			bMovingRight = true;
		}
	}

	//restrict X Position to screen bounds
	if (newXPos < 0.0f || (newXPos + csc->GetTexWidth()) >= GetGame()->GetMap()->GetCalculatedLevelWidth()) {
		newXPos = GetPosition().x;
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


	SetPosition(Vector2(newXPos, newYPos));
	csc->GetDestRect()->x = GetPosition().x - GetGame()->mCamera.x;
	csc->GetDestRect()->y = GetPosition().y;
}
