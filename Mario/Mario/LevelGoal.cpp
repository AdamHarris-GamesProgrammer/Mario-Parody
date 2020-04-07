#include "LevelGoal.h"
#include "Game.h"
#include "CollisionComponent.h"

LevelGoal::LevelGoal(Game* game, SDL_Rect* srcRect, SDL_Rect* destRect) :Tile(game,srcRect,destRect, false)
{
	mGame->GetCurrentScreen()->AddLevelGoal(this); //Adds the level goal to the current gameScreen
}

LevelGoal::~LevelGoal()
{

}
