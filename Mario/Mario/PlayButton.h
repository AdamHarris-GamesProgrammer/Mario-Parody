#pragma once

#include "ButtonComponent.h"

class PlayButton : public Actor, public ButtonComponent
{
public:
	PlayButton(class Game* game, Vector2 position);
	~PlayButton();

	void OnMouseButtonDown() override;
	void OnMouseOver() override;
};

