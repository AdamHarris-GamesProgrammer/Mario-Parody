#include "Component.h"
#include "Actor.h"

Component::Component(class Actor* owner, int updateOrder /*= 100*/) : mOwner(owner), mUpdateOrder(updateOrder) //sets default values
{
	//adds this component to the owners mComponents vector
	mOwner->AddComponent(this);
}

Component::~Component()
{
	//removes this component from the owners mComponents vector
	mOwner->RemoveComponent(this);
}

//virtual function
void Component::Update(float deltaTime)
{
}
