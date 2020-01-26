#include "CollisionComponent.h"

bool Intersect(const SDL_Rect& a, const SDL_Rect& b)
{
	int bottom1 = a.y + a.h; //the bottom of the first game object
	int bottom2 = b.y + b.h; //the bottom of the second game object

	int left1 = a.x; //the left side of the first game object
	int left2 = b.x; //the left side of the second game object

	int right1 = a.x + a.w; //the right side of the first game object
	int right2 = b.x + b.w; //the right side of the second game object

	int top1 = a.y; //the top of the first game object
	int top2 = b.y; //the top of the second game object

	if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2)) { //if there is a overlapping side
		return true;
	}
	else {
		return false;
	}
}

bool Intersect(const SDL_Rect* a, const SDL_Rect* b)
{
	int bottom1 = a->y + a->h; //the bottom of the first game object
	int bottom2 = b->y + b->h; //the bottom of the second game object

	int left1 = a->x; //the left side of the first game object
	int left2 = b->x; //the left side of the second game object

	int right1 = a->x + a->w; //the right side of the first game object
	int right2 = b->x + b->w; //the right side of the second game object

	int top1 = a->y; //the top of the first game object
	int top2 = b->y; //the top of the second game object

	if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2)) { //if there is a overlapping side
		return true;
	}
	else {
		return false;
	}
}

CollisionComponent::CollisionComponent(class Actor* owner) : Component(owner)
{

}
