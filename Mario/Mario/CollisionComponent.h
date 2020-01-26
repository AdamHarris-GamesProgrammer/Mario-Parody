#pragma once
#include "Component.h"
#include "SDL.h"

class CollisionComponent : public Component
{
public:
	CollisionComponent(class Actor* owner);

private:


};

bool Intersect(const SDL_Rect& a, const SDL_Rect& b);
bool Intersect(const SDL_Rect* a, const SDL_Rect* b);

