#pragma once
#include "Actor.h"
#include "SDL.h"
#include "Constants.h"
#include "Sound.h"
#include "Music.h"

#include <vector>

class Mario : public Actor
{
public:
	Mario(class Game* game);
	~Mario();

	//Overrides the UpdateActor method from the Actor base class
	void UpdateActor(float deltaTime) override;

	//Handles all the events 
	void HandleEvents(const uint8_t* state);

	//Changes the player tile
	void ChangePlayerTile(Vector2 position);

	//Getter/Setter for bDead variables
	bool GetDead() const { return bDead; }
	void SetDead(bool newValue) { bDead = newValue; }

	//Sets the player Position
	void SetPlayerPosition(const Vector2& newValue);

private:
	class CharacterSpriteComponent* csc;

	class CircleComponent* mCircle;

	//Grounded check for when to add gravity
	bool bGrounded = true;

	//Jump control variables
	bool bCanJump;
	bool bJumping;
	
	//Sound manager
	Sound* mSoundManager;

	//sound effects
	Mix_Chunk* mJumpSound = nullptr;
	Mix_Chunk* mCoinSound = nullptr;
	Mix_Chunk* mDeathSound = nullptr;
	Mix_Chunk* mHeadHitSound = nullptr;
	Mix_Chunk* mLevelWonSound = nullptr;
	Mix_Chunk* mGameOverSound = nullptr;
	Mix_Chunk* mEnemyKillSound = nullptr;

	//player death variable
	bool bDead = false;

	//Jump force for the character
	float mJumpForce;

	//X velocity (used for movement)
	float mPlayerVelX;
	
	//movement speed (used in movement calculations)
	float mMovementSpeed = 5.0f;

	//Animation sets for the character
	std::vector<SDL_Texture*> mIdleAnims;
	std::vector<SDL_Texture*> mWalkingAnims;
	std::vector<SDL_Texture*> mJumpingAnims;

	//Checks for collisions against functional game objects
	void CollisionChecks();

	//Jumping method
	void Jump(Vector2& newPos, float deltaTime);

	bool mWalking = false;
};

