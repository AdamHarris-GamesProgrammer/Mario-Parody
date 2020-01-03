#pragma once
class Component
{
public:
	//the lower the update order the earlier the component will update
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);

	int GetUpdateOrder() { return mUpdateOrder; }

protected:
	class Actor* mOwner;

	int mUpdateOrder;
};

