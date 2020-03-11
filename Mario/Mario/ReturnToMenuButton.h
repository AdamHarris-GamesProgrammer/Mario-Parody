#pragma once
#include "ButtonComponent.h"
class ReturnToMenuButton : public ButtonComponent, public Actor
{
public:
	ReturnToMenuButton(class Game* game, Vector2 position);
	~ReturnToMenuButton();

	void OnMouseButtonDown() override;
};

