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
#include "PowBlock.h"

/*TODO
Music is delayed
Take another crack at collision system
*/

Mario::Mario(class Game* game) : Actor(game)
{
	csc = new CharacterSpriteComponent(this);

	//Idle animations
	mIdleAnims.reserve(4);
	mIdleAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Mario/MarioIdle01.png", true));
	mIdleAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Mario/MarioIdle02.png", true));
	mIdleAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Mario/MarioIdle03.png", true));
	mIdleAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Mario/MarioIdle04.png", true));

	csc->SetAnimTextures(mIdleAnims);
	csc->SetAnimFPS(4);

	//Walking animations
	mWalkingAnims.reserve(3);
	mWalkingAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Mario/MarioWalk01.png", true));
	mWalkingAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Mario/MarioWalk02.png", true));
	mWalkingAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Mario/MarioWalk03.png", true));

	//Jumping animation
	mJumpingAnims.push_back(mGame->GetEngine()->GetTexture("Assets/Characters/Mario/MarioJump01.png", true));

	//Circle collision system
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.0f);

	//Loads all sound effects and creates a instance of the sound class
	mSoundManager = new Sound();
	mJumpSound = mSoundManager->LoadSoundEffect("Assets/Audio/Mario/Jump.wav");
	mCoinSound = mSoundManager->LoadSoundEffect("Assets/Audio/Mario/Coin.wav");
	mDeathSound = mSoundManager->LoadSoundEffect("Assets/Audio/Mario/Die.wav");
	mHeadHitSound = mSoundManager->LoadSoundEffect("Assets/Audio/Mario/Thwomp.wav");
	mLevelWonSound = mSoundManager->LoadSoundEffect("Assets/Audio/Mario/Flagpole.wav");
	mGameOverSound = mSoundManager->LoadSoundEffect("Assets/Audio/Mario/Game Over.wav");
	mEnemyKillSound = mSoundManager->LoadSoundEffect("Assets/Audio/Mario/Kick.wav");

	//Sets velocity to 0
	mPlayerVelX = 0.0f;

	//allows player to jump by default
	bCanJump = true;
}

Mario::~Mario()
{
	RemoveComponent(csc);
	RemoveComponent(mCircle);

	delete csc;
	delete mCircle;

	csc = nullptr;
	mCircle = nullptr;
}

void Mario::UpdateActor(float deltaTime)
{
	if (!mGame->IsGamePaused()) {
		Actor::UpdateActor(deltaTime);

		if (!bDead) {
			if (bJumping) {
				csc->SetAnimTextures(mJumpingAnims);
			}
			else
			{
				if (!mWalking) {
					csc->SetAnimTextures(mIdleAnims);
				}
				else
				{
					csc->SetAnimTextures(mWalkingAnims);
				}
			}

			Vector2 newPosition = GetPosition();

			if (mPlayerVelX != 0) {
				newPosition.x += mPlayerVelX * mMovementSpeed * deltaTime;
			}

			if (bJumping) {
				Jump(newPosition, deltaTime);
				csc->SetAnimTextures(mJumpingAnims);
			}

			if (newPosition.y > mGame->GetCurrentScreen()->GetMap()->GetCalculatedLevelHeight() + csc->GetTexHeight()) {
				bDead = true;
				mGame->OnPlayerDeath();
			}

			//tiles in all four directions
			int leftTile = (int)newPosition.x / TILE_WIDTH;
			int rightTile = (int)(newPosition.x + csc->GetTexWidth()) / TILE_WIDTH;
			int topTile = (int)newPosition.y / TILE_HEIGHT;
			int bottomTile = (int)(newPosition.y + csc->GetTexHeight()) / TILE_HEIGHT;

			//gets the six surrounding tiles
			int topLeftTile = mGame->GetCurrentScreen()->GetMap()->GetValueAtTile(topTile, leftTile);
			int topRightTile = mGame->GetCurrentScreen()->GetMap()->GetValueAtTile(topTile, rightTile);
			int midLeftTile = mGame->GetCurrentScreen()->GetMap()->GetValueAtTile(bottomTile - 1, leftTile);
			int midRightTile = mGame->GetCurrentScreen()->GetMap()->GetValueAtTile(bottomTile - 1, rightTile);
			int bottomLeftTile = mGame->GetCurrentScreen()->GetMap()->GetValueAtTile(bottomTile, leftTile);
			int bottomRightTile = mGame->GetCurrentScreen()->GetMap()->GetValueAtTile(bottomTile, rightTile);

			//Top Collisions
			if ((topLeftTile == BRICK)
			|| (topRightTile == BRICK)) { 
				newPosition.y = GetPosition().y;
				mJumpForce = 0.0f;
				mSoundManager->PlaySoundEffect(mHeadHitSound);
			}

			if (topLeftTile == GOLDBRICK) {
				PowBlock* collidedBlock = (PowBlock*)mGame->GetCurrentScreen()->GetMap()->GetTileAt(topTile, leftTile);
				collidedBlock->TakeDamage();
				mGame->GetCurrentScreen()->FlipKoopas();
				mSoundManager->PlaySoundEffect(mCoinSound);
				newPosition.y = GetPosition().y;
				mJumpForce = 0.0f;
			}
			else if (topRightTile == GOLDBRICK) {
				PowBlock* collidedBlock = (PowBlock*)mGame->GetCurrentScreen()->GetMap()->GetTileAt(topTile, rightTile);
				collidedBlock->TakeDamage();
				mGame->GetCurrentScreen()->FlipKoopas();
				mSoundManager->PlaySoundEffect(mCoinSound);
				newPosition.y = GetPosition().y;
				mJumpForce = 0.0f;
			}

			//Mid Collisions
			if ((midLeftTile == BRICK || midLeftTile >= PIPE_HORIZONTAL) || (midRightTile == BRICK || midRightTile >= PIPE_HORIZONTAL)) { //All pipes have values above 96
				newPosition.x = GetPosition().x;
			}

			//Bottom collisions
			if ((bottomRightTile== AIR			&& bottomLeftTile == AIR)
			|| (bottomRightTile == DROPBRICK	&& bottomLeftTile == DROPBRICK)
			|| (bottomRightTile == KOOPATURN	|| bottomLeftTile == KOOPATURN)
			|| (bottomRightTile == COIN			|| bottomLeftTile == COIN)
			|| (bottomRightTile == KOOPA		|| bottomLeftTile == KOOPA)
			|| (bottomRightTile == LEVELGOAL	|| bottomLeftTile == LEVELGOAL)
			|| (bottomRightTile == PLAYERSPAWN	|| bottomLeftTile == PLAYERSPAWN)) {
				bGrounded = false;
				newPosition.y += GRAVITY * deltaTime;
			}
			else
			{
				bCanJump = true;
				bGrounded = true;
			}


			//constrains player to X level bounds
			if (newPosition.x < 0.0f || (newPosition.x + csc->GetTexWidth()) >= mGame->GetCurrentScreen()->GetMap()->GetCalculatedLevelWidth()) {
				newPosition.x = GetPosition().x;
			}

			//Sets the players position and dest rect to work with the camera system
			SetPlayerPosition(newPosition);
			//checks for collision with coins, enemies and level goals
			CollisionChecks();
		}
		else //if player is dead
		{
			//player falls off screen
			Vector2 newPosition = GetPosition();
			newPosition.y += GRAVITY * deltaTime;
			SetPlayerPosition(newPosition);
		}
	}
	else
	{
		SetPlayerPosition(GetPosition());
	}
}

void Mario::HandleEvents(const uint8_t* state)
{
	mPlayerVelX = 0.0f;
	if (!mGame->IsGamePaused() && !mGame->IsGameOver()) {

		mWalking = false;
		if (!bDead) {
			if (state[SDL_SCANCODE_A]) {
				csc->SetRendererFlip(SDL_FLIP_HORIZONTAL);
				mPlayerVelX += -25.0f;
				mWalking = true;
			}
			else if (state[SDL_SCANCODE_D]) {
				csc->SetRendererFlip(SDL_FLIP_NONE);
				mPlayerVelX += 25.0f;
				mWalking = true;
			}

			if (state[SDL_SCANCODE_D] == 0 && state[SDL_SCANCODE_A] == 0) {
				mWalking = false;
			}

			if (state[SDL_SCANCODE_SPACE]) {
				if (bGrounded) {
					if (!bJumping && bCanJump) {

						mSoundManager->PlaySoundEffect(mJumpSound);
						mJumpForce = INITIAL_JUMP_FORCE;
						bGrounded = false;
						bJumping = true;
						bCanJump = false;
					}
				}
			}
		}
	}


}

void Mario::ChangePlayerTile(Vector2 position)
{
	mGame->GetCurrentScreen()->GetMap()->ChangeTileAt((int)position.y / TILE_HEIGHT, (int)position.x / TILE_WIDTH, -1);
}

void Mario::SetPlayerPosition(const Vector2& newValue)
{
	Actor::SetPosition(newValue);
	csc->GetDestRect()->x = (int)GetPosition().x - (int)mGame->mCamera.x;
	csc->GetDestRect()->y = (int)GetPosition().y;
}

void Mario::CollisionChecks()
{
	if (!mGame->IsGameOver()) {
		//checks to see if a coin has been picked up
		for (auto coin : mGame->GetCurrentScreen()->GetCoins()) {
			if (Intersect(*mCircle, *(coin->GetCircle()))) {
				mGame->GetCurrentScreen()->GetMap()->ChangeTileAt(((int)coin->GetPosition().y / TILE_HEIGHT), ((int)coin->GetPosition().x / TILE_WIDTH), -1);
				coin->SetState(EDead);
				mSoundManager->PlaySoundEffect(mCoinSound);
				mGame->IncrementScore();
			}
		}

		//checks to see if the player is colliding with the level goal
		if (mGame->GetCurrentScreen()->GetLevelGoal() != nullptr) {
			if (Intersect(*csc->GetDestRect(), *(mGame->GetCurrentScreen()->GetLevelGoal()->GetDestRect()))) {
				if (!mGame->IsGameOver()) {
					mGame->LoadNextLevelMenu();
					mSoundManager->PlaySoundEffect(mLevelWonSound);
				}
			}
		}

		for (auto enemy : mGame->GetCurrentScreen()->GetKoopas()) {
			if (enemy != nullptr) {
				if (Intersect(*mCircle, *(enemy->GetCircle()))) {
					if (enemy->GetFlipped()) {
						enemy->SetAlive(false);
						mSoundManager->PlaySoundEffect(mEnemyKillSound);
					}
					else
					{
						mSoundManager->PlaySoundEffect(mDeathSound);
						mGame->OnPlayerDeath();
						bDead = true;
					}
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
		mJumpForce = 0.0f;
	}
}

