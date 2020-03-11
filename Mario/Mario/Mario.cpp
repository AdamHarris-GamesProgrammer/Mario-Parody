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



Mario::Mario(class Game* game) : Actor(game)
{
	csc = new CharacterSpriteComponent(this);

	mIdleAnims.push_back(game->GetEngine()->GetTexture("Assets/Characters/Mario/MarioIdle01.png", true));
	mIdleAnims.push_back(game->GetEngine()->GetTexture("Assets/Characters/Mario/MarioIdle02.png", true));
	mIdleAnims.push_back(game->GetEngine()->GetTexture("Assets/Characters/Mario/MarioIdle03.png", true));
	mIdleAnims.push_back(game->GetEngine()->GetTexture("Assets/Characters/Mario/MarioIdle04.png", true));

	csc->SetAnimTextures(mIdleAnims);
	csc->SetAnimFPS(4);

	mWalkingAnims.push_back(game->GetEngine()->GetTexture("Assets/Characters/Mario/MarioWalk01.png", true));
	mWalkingAnims.push_back(game->GetEngine()->GetTexture("Assets/Characters/Mario/MarioWalk02.png", true));
	mWalkingAnims.push_back(game->GetEngine()->GetTexture("Assets/Characters/Mario/MarioWalk03.png", true));



	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.0f);

	marioSound = new Sound();
	mJumpSound = marioSound->LoadSoundEffect("Assets/Audio/Mario/Jump.wav");
	mCoinSound = marioSound->LoadSoundEffect("Assets/Audio/Mario/Coin.wav");
	mDeathSound = marioSound->LoadSoundEffect("Assets/Audio/Mario/Die.wav");
	mHeadHitSound = marioSound->LoadSoundEffect("Assets/Audio/Mario/Thwomp.wav");
	mLevelWonSound = marioSound->LoadSoundEffect("Assets/Audio/Mario/Flagpole.wav");
	mGameOverSound = marioSound->LoadSoundEffect("Assets/Audio/Mario/Game Over.wav");
	mEnemyKillSound = marioSound->LoadSoundEffect("Assets/Audio/Mario/Kick.wav");

	mPlayerVelX = 0.0f;

	bCanJump = true;
}

Mario::~Mario()
{
	RemoveComponent(csc);
	RemoveComponent(mCircle);

	delete csc;
	delete mCircle;

	csc = NULL;
	mCircle = NULL;
}

void Mario::UpdateActor(float deltaTime)
{
	if (!GetGame()->IsGamePaused()) {
		Actor::UpdateActor(deltaTime);

		if (!bDead) {
			if (!mWalking) {
				csc->SetAnimTextures(mIdleAnims);
			}
			else
			{
				csc->SetAnimTextures(mWalkingAnims);
			}


			Vector2 newPosition = GetPosition();

			if (mPlayerVelX != 0) {
				newPosition.x += mPlayerVelX * mMovementSpeed * deltaTime;
			}

			if (bJumping) {
				Jump(newPosition, deltaTime);
				csc->SetAnimTextures(mJumpingAnims);
			}

			int leftTile = (int)newPosition.x / TILE_WIDTH;
			int rightTile = (int)(newPosition.x + csc->GetTexWidth()) / TILE_WIDTH;
			int topTile = (int)newPosition.y / TILE_HEIGHT;
			int bottomTile = (int)(newPosition.y + csc->GetTexHeight()) / TILE_HEIGHT;

			int topLeftTile = GetGame()->GetMap()->GetValueAtTile(topTile, leftTile);
			int topRightTile = GetGame()->GetMap()->GetValueAtTile(topTile, rightTile);
			int midLeftTile = GetGame()->GetMap()->GetValueAtTile(bottomTile - 1, leftTile);
			int midRightTile = GetGame()->GetMap()->GetValueAtTile(bottomTile - 1, rightTile);
			int bottomLeftTile = GetGame()->GetMap()->GetValueAtTile(bottomTile, leftTile);
			int bottomRightTile = GetGame()->GetMap()->GetValueAtTile(bottomTile, rightTile);

			//Top Collisions
			if ((topLeftTile != AIR && topLeftTile != COIN && topLeftTile != KOOPATURN && topLeftTile != GOLDBRICK && topLeftTile != PIPE_HORIZONTAL && topLeftTile != PIPE_LEFTEND && topLeftTile != PIPE_RIGHTEND && topLeftTile != PIPE_VERTICAL && topLeftTile != PIPE_VERTICAL_TOP)
				|| (topRightTile != AIR && topRightTile != COIN && topRightTile != KOOPATURN && topRightTile != GOLDBRICK && topRightTile != PIPE_HORIZONTAL && topRightTile != PIPE_LEFTEND && topRightTile != PIPE_RIGHTEND && topRightTile != PIPE_VERTICAL && topRightTile != PIPE_VERTICAL_TOP)) {
				newPosition.y = GetPosition().y;
				mJumpForce = 0.0f;
				marioSound->PlaySoundEffect(mHeadHitSound);
			}

			//Mid Collisions
			if ((midLeftTile == BRICK || midLeftTile == PIPE_HORIZONTAL || midLeftTile == PIPE_LEFTEND || midLeftTile == PIPE_RIGHTEND || midLeftTile == PIPE_VERTICAL || midLeftTile == PIPE_VERTICAL_TOP)
				|| (midRightTile == BRICK || midRightTile == PIPE_HORIZONTAL || midRightTile == PIPE_LEFTEND || midRightTile == PIPE_RIGHTEND || midRightTile == PIPE_VERTICAL || midRightTile == PIPE_VERTICAL_TOP)) {
				newPosition.x = GetPosition().x;
			}

			//jumping mid air collisions
			if (bJumping) {
				if (bottomLeftTile == BRICK || bottomRightTile == BRICK) {
					newPosition.x = GetPosition().x;
				}
				if (midLeftTile == BRICK || midRightTile == BRICK) {
					newPosition.x = GetPosition().x;
				}
				if (topLeftTile == BRICK || topRightTile == BRICK) {
					newPosition.x = GetPosition().x;
				}
			}

			//Bottom collisions
			if ((bottomRightTile == AIR && bottomLeftTile == AIR)
				|| (bottomRightTile == DROPBRICK && bottomLeftTile == DROPBRICK)
				|| (bottomRightTile == KOOPATURN || bottomLeftTile == KOOPATURN)
				|| (bottomRightTile == COIN || bottomLeftTile == COIN)
				|| (bottomRightTile == KOOPA || bottomLeftTile == KOOPA)
				|| (bottomRightTile == LEVELGOAL || bottomLeftTile == LEVELGOAL)) {
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
	else
	{
		SetPlayerPosition(GetPosition());
	}
	

}

void Mario::HandleEvents(const uint8_t* state)
{
	if (!GetGame()->IsGamePaused()) {
		mPlayerVelX = 0.0f;

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

						marioSound->PlaySoundEffect(mJumpSound);
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
	GetGame()->GetMap()->ChangeTileAt((int)position.y / TILE_HEIGHT, (int)position.x / TILE_WIDTH, -1);
}

void Mario::SetPlayerPosition(const Vector2& newValue)
{
	Actor::SetPosition(newValue);
	csc->GetDestRect()->x = (int)GetPosition().x - (int)GetGame()->mCamera.x;
	csc->GetDestRect()->y = (int)GetPosition().y;
}

void Mario::CollisionChecks()
{
	if (!mGame->IsGameOver()) {
		//checks to see if a coin has been picked up
		for (auto coin : GetGame()->GetCoins()) {
			if (Intersect(*mCircle, *(coin->GetCircle()))) {
				GetGame()->GetMap()->ChangeTileAt(((int)coin->GetPosition().y / TILE_HEIGHT), ((int)coin->GetPosition().x / TILE_WIDTH), -1);
				coin->SetState(EDead);
				marioSound->PlaySoundEffect(mCoinSound);
				mGame->IncrementScore();
			}
		}

		//checks to see if the player is colliding with the level goal
		if (GetGame()->GetLevelGoal() != nullptr) {
			if (Intersect(*csc->GetDestRect(), *(GetGame()->GetLevelGoal()->GetDestRect()))) {
				GetGame()->LoadNextLevelMenu();
				marioSound->PlaySoundEffect(mLevelWonSound);
			}
		}

		for (auto enemy : GetGame()->GetKoopas()) {
			if (enemy != nullptr) {
				if (Intersect(*mCircle, *(enemy->GetCircle()))) {
					//TODO setup koopa active check
					if (enemy->GetFlipped()) {
						enemy->SetAlive(false);
						marioSound->PlaySoundEffect(mEnemyKillSound);
					}
					else
					{
						marioSound->PlaySoundEffect(mDeathSound);
						//TODO: Uncomment this line to enable player death
						bDead = true;
					}
				}
			}
		}

		for (auto powBlock : GetGame()->GetPowBlocks())
		{
			if (powBlock != nullptr) {
				if (Intersect(csc->GetDestRect(), powBlock->GetDestRect())) {
					if (bJumping) {
						for (auto enemy : mGame->GetKoopas()) {
							enemy->SetFlipped(true);
						}
						powBlock->TakeDamage();
						mJumpForce = 0.0f;
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

