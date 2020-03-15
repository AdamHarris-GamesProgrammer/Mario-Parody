#pragma once

#include <vector>
#include "Math.h"

class Actor
{
public:

	//These states determine if an actor is supposed to be rendered/updated or removed 
	//When they are active an actor will be rendered and updated
	//When they are paused they will not be rendered or updated
	//When they are dead they are placed in a vector of actors that need to be deleted
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	//Constructor takes a reference to the game
	Actor(class Game* game);
	virtual ~Actor();

	//Update will update all of the components and the actor themselves
	void Update(float deltaTime);

	//UpdateComponents calls the update method for each of the components 
	void UpdateComponents(float deltaTime);
	
	//UpdateActor will be overridden by each actor that needs to override it 
	virtual void UpdateActor(float deltaTime);

	//Getter/Setter for the position
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& newValue) { mPosition = newValue; }

	//Getter/Setter for the scale
	float GetScale() const { return mScale; }
	void SetScale(float newValue) { mScale = newValue; }

	//Getter/Setter for the actor rotation
	float GetRotation() const { return mRotation; }
	void SetRotation(float newValue) { mRotation = newValue; }

	//Getter/Setter for the actor state
	State GetState() const { return mState; }
	void SetState(State newState) { mState = newState; }

	//Gets the direction that the actor is facing 
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	//Gets a reference to the game class
	class Game* GetGame() { return mGame; }

	//Adds a component (Called in the component class constructor)
	void AddComponent(class Component* component);

	//Removes a component (Called in the component class destructor)
	void RemoveComponent(class Component* component);

private:
	//Holds the state for the current Actor
	State mState;

	//Holds the position for the current Actor
	Vector2 mPosition;
	
	//Holds the Actor scale
	float mScale;

	//Holds the Actors rotation
	float mRotation;

	//This is a vector of all the Component objects that a object has 
	std::vector<class Component*> mComponents;

protected:
	//All derived objects will have this as a member
	class Game* mGame;
};

