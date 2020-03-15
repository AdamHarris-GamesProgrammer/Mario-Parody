#pragma once
class Component
{
public:
	//the lower the update order the earlier the component will update
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	//virutal update method as each component will have a different use
	virtual void Update(float deltaTime);

	//Gets the update order of the component 
	int GetUpdateOrder() { return mUpdateOrder; }

	//Returns the owner of the actor
	class Actor* GetOwner() { return mOwner; }

protected:
	//Allows any derived component to access the owner
	class Actor* mOwner;

	//Allows any derived component to access the update order
	int mUpdateOrder;
};

