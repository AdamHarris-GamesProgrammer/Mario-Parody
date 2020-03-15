#pragma once

#include "ButtonComponent.h"

class PlayButton : public Actor, public ButtonComponent
{
public:
	PlayButton(class Game* game, Vector2 position);
	//overrides the OnMouseButtonDown event
	void OnMouseButtonDown() override;
};

