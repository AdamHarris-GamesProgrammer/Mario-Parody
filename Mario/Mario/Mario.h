#pragma once
#include "Actor.h"
#include "SDL.h"

class Mario : public Actor
{
public:
	Mario(class Game* game);
	void UpdateActor(float deltaTime) override;
	void HandleEvents(const uint8_t* state);
	float GetMovementSpeed() const { return mMovementSpeed; }

private:
	float mMovementSpeed;
};

