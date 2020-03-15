#include "Actor.h"
#include "Game.h"
#include "Component.h"

#include <algorithm>

//Constructor sets the default values for each member variable 
Actor::Actor(class Game* game) : mState(EActive), mPosition(Vector2::Zero), mScale(1.0f), mRotation(0.0f), mGame(game)
{
	//Calls the AddActor method in the BlueSky class 
	mGame->GetEngine()->AddActor(this);
}

Actor::~Actor()
{
	//Calls the RemoveActor method in the BlueSky class
	mGame->GetEngine()->RemoveActor(this);

	//Deletes all of the components in the mComponents array
	while (!mComponents.empty()) { //Repeats while the loop is not empty
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	//If the actor is active then update the components and actor itself
	if (mState == EActive) {
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	//cycles through each of the components and calls the update method in each
	for (auto comp : mComponents) {
		comp->Update(deltaTime);
	}
}

//virtual function
void Actor::UpdateActor(float deltaTime)
{
	//This will be unique for each actor e.g. This is where Mario's movement code is
}

void Actor::AddComponent(class Component* component)
{
	//Gets the update order of the component that is being added
	int myOrder = component->GetUpdateOrder();

	//Iterator to go through each of the objects in the components vector
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter) {
		//The lower the update order the higher priority a component is 
		if (myOrder < (*iter)->GetUpdateOrder()) {
			break;
		}
	}
	//inserts component before the position of the iterator
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(class Component* component)
{
	//searches mComponent vector for the component and deletes it
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end()) {
		mComponents.erase(iter);
	}
}
