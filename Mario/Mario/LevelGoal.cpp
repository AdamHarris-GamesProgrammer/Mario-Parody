#include "LevelGoal.h"
#include "Game.h"
#include "CollisionComponent.h"

LevelGoal::LevelGoal(Game* game, SDL_Rect* srcRect, SDL_Rect* destRect) :Tile(game,srcRect,destRect, 3)
{
	mGame->GetCurrentScreen()->AddLevelGoal(this);
}

LevelGoal::~LevelGoal()
{

}
