#pragma once
#include "Actor.h"
class Koopa : public Actor
{
public:
	Koopa(class Game* game);
	~Koopa();

	void UpdateActor(float deltaTime) override;

private:
	class CharacterSpriteComponent* csc;
	class CircleComponent* mCircle;

	bool bMovingRight = true;

	float mMovementSpeed = 25.0f;
};

