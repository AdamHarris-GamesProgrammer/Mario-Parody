#pragma once
#include "Actor.h"
#include "SDL.h"
class Koopa : public Actor
{
public:
	Koopa(class Game* game);
	~Koopa();

	//overrides the UpdateActor method from the Actor class
	void UpdateActor(float deltaTime) override;

	//Getters/Setters for active and flipped variables
	void SetFlipped(bool newValue) { bFlipped = newValue; }
	void SetAlive(bool newValue) { bAlive = newValue; }
	bool GetFlipped() const { return bFlipped; }
	bool GetAlive() const { return bAlive; }

	//Collision circle
	class CircleComponent* GetCircle() const { return mCircle; }

private:
	class CharacterSpriteComponent* csc;
	class CircleComponent* mCircle;

	//controls movement direction
	bool bMovingRight = true;
	bool bAlive = true;

	//flipping related variables
	bool bFlipped = false;

	float flippedTimer;
	const float flippedDuration = 3.0f;

	float mMovementSpeed = 25.0f;

	//Animation vectors
	std::vector<SDL_Texture*> walkingAnims; 
	std::vector<SDL_Texture*> flippedAnims;
};

