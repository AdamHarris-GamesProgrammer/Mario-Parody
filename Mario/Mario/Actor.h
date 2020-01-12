#pragma once

#include <vector>
#include "Math.h"

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);


	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& newValue) { mPosition = newValue; }

	float GetScale() const { return mScale; }
	void SetScale(float newValue) { mScale = newValue; }

	float GetRotation() const { return mRotation; }
	void SetRotation(float newValue) { mRotation = newValue; }

	State GetState() const { return mState; }
	void SetState(State newState) { mState = newState; }

	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	class Game* GetGame() { return mGame; }


	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	State mState;

	Vector2 mPosition;
	float mScale;
	float mRotation;

	std::vector<class Component*> mComponents;

protected:
	class Game* mGame;


};

