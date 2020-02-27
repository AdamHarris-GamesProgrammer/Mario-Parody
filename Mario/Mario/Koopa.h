#pragma once
#include "Actor.h"
#include "SDL.h"
class Koopa : public Actor
{
public:
	Koopa(class Game* game);
	~Koopa();

	void UpdateActor(float deltaTime) override;

	void SetFlipped(bool newValue) { bFlipped = newValue; }
	void SetAlive(bool newValue) { bAlive = newValue; }
	bool GetFlipped() const { return bFlipped; }
	bool GetAlive() const { return bAlive; }

	class CircleComponent* GetCircle() const { return mCircle; }

private:
	class CharacterSpriteComponent* csc;
	class CircleComponent* mCircle;

	bool bMovingRight = true;
	bool bAlive = true;
	bool bFlipped = false;

	float flippedTimer;
	const float flippedDuration = 3.0f;

	float mMovementSpeed = 25.0f;

	std::vector<SDL_Texture*> walkingAnims; 

	std::vector<SDL_Texture*> flippedAnims;
};

