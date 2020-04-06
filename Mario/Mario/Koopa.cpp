#include "Koopa.h"
#include "CharacterSpriteComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "TileMapComponent.h"
#include "TileValues.h"

Koopa::Koopa(class Game* game) : Actor(game)
{
	//32,30 is the texture width and height
	csc = new CharacterSpriteComponent(this, 110, 32, 30);
	
	//Walking animations
	walkingAnims.reserve(4);
	walkingAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Koopa/Koopa01.png"));
	walkingAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Koopa/Koopa02.png"));
	walkingAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Koopa/Koopa03.png"));
	walkingAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Koopa/Koopa04.png"));
	
	//Flipped over animations
	flippedAnims.reserve(4);
	flippedAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Koopa/KoopaFlipped01.png"));
	flippedAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Koopa/KoopaFlipped02.png"));
	flippedAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Koopa/KoopaFlipped03.png"));
	flippedAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Koopa/KoopaFlipped04.png"));

	//both animations are 4 frames
	csc->SetAnimFPS(4);

	//Sets the textures
	csc->SetAnimTextures(walkingAnims);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(8.0f);

	//Sets the flipped timer equal to the duration of the flipping effect
	flippedTimer = flippedDuration;
}

Koopa::~Koopa()
{
	RemoveComponent(csc);
	RemoveComponent(mCircle);

	delete csc;
	delete mCircle;

	csc = NULL;
	mCircle = NULL;
}

void Koopa::UpdateActor(float deltaTime)
{
	Vector2 newPosition = GetPosition(); //the newPosition variable is used to test if the new position is valid before the character actually moves there
	if (bAlive) { //if alive
		if (!bFlipped) { //if not flipped over

			//gets the tiles in all four directions
			int leftTile = newPosition.x / TILE_WIDTH;
			int rightTile = (newPosition.x + csc->GetTexWidth()) / TILE_WIDTH;
			int bottomTile = (newPosition.y + csc->GetTexHeight()) / TILE_HEIGHT;

			//gets the values at the tiles to the mid left and mid right
			int midLeftTile = mGame->GetCurrentScreen()->GetMap()->GetValueAtTile(bottomTile - 1, leftTile);
			int midRightTile = mGame->GetCurrentScreen()->GetMap()->GetValueAtTile(bottomTile - 1, rightTile);

			if (bMovingRight) { //if moving right
				newPosition.x += mMovementSpeed * deltaTime; //add to the newPosition variable

				//checks right tile collision
				if (midRightTile == BRICK || midRightTile == KOOPATURN || midRightTile >= PIPE_HORIZONTAL) { //if midright tile is anything they cant walk through
					newPosition.x = GetPosition().x; //reset position for this frame
					bMovingRight = false; //makes them move left
				}
			}
			else
			{
				newPosition.x -= mMovementSpeed * deltaTime; //subtract from the newPosition variable

				if (midLeftTile == BRICK || midLeftTile == KOOPATURN || midLeftTile >= PIPE_HORIZONTAL) { //if midleft tile is anything they cant walk through
					newPosition.x = GetPosition().x; //resets position for this frame
					bMovingRight = true; //makes them move right
				}
			}

			//restrict X Position to screen bounds
			if (newPosition.x < 0.0f || (newPosition.x + csc->GetTexWidth()) >= mGame->GetCurrentScreen()->GetMap()->GetCalculatedLevelWidth()) {
				newPosition.x = GetPosition().x;
				bMovingRight = !bMovingRight;
			}


			//orient sprite
			if (bMovingRight) {
				csc->SetRendererFlip(SDL_FLIP_NONE);
			}
			else
			{
				csc->SetRendererFlip(SDL_FLIP_HORIZONTAL); //makes sprite flip horizontally so it looks like they are going left
			}


		}
		else //if flipped over
		{
			//set the animation to the flippedAnims
			csc->SetAnimTextures(flippedAnims);
			//decrease the timer
			flippedTimer -= deltaTime;
			if (flippedTimer <= 0) {
				//reset values 
				bFlipped = false;
				csc->SetAnimTextures(walkingAnims);
				flippedTimer = flippedDuration;
			}

		}

		//Sets position and camera related details
		SetPosition(newPosition);
		csc->GetDestRect()->x = GetPosition().x - mGame->mCamera.x;
		csc->GetDestRect()->y = GetPosition().y;
	}
	else { //if dead
		//increments score
		mGame->IncrementScore(100);

		//removes the koopa from the mKoopa vector in the game screen class
		mGame->GetCurrentScreen()->RemoveKoopa(this);
		delete this;
	}
	
}
