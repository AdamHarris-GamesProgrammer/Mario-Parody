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
	if (mState == EActive) {
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents) {
		comp->Update(deltaTime);
	}
}

//virtual function
void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(class Component* component)
{
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter) {
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
