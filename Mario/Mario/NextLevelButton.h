#pragma once
#include "Actor.h"
#include "ButtonComponent.h"
#include "TextSpriteComponent.h"

class NextLevelButton : public Actor, public ButtonComponent
{
public:
	NextLevelButton(class Game* game, Vector2 position);
	 //overrides the OnMouseButtonDown event
	void OnMouseButtonDown() override;
};

