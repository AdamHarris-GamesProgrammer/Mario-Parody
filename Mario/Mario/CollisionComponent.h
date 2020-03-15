#pragma once
#include "Component.h"
#include "SDL.h"

class CollisionComponent : public Component
{
public:
	CollisionComponent(class Actor* owner);

private:
};
//Intersect methods written on outside of method so they can be called without an instance of the collision component class
bool Intersect(const SDL_Rect& a, const SDL_Rect& b);
bool Intersect(const SDL_Rect* a, const SDL_Rect* b);

