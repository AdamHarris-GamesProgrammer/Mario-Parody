#include "PowBlock.h"
#include "Game.h"
#include "TileMapComponent.h"
PowBlock::PowBlock(class Game* game, SDL_Rect* srcRect, SDL_Rect* destRect) : Tile(game, srcRect, destRect, 32)
{

}

PowBlock::~PowBlock()
{

}

void PowBlock::TakeDamage()
{
	if (bActive) {
		healthLeft--;
		SDL_Rect* rect = new SDL_Rect{ (4 - healthLeft) * TILE_WIDTH, 32, TILE_WIDTH, TILE_HEIGHT };
		SetSrcRect(rect);
		mGame->IncrementScore(20);
		if (healthLeft <= 0)
		{
			bActive = false;
			mGame->IncrementScore(100);
			GetGame()->RemovePowBlock(this);
			GetGame()->GetMap()->ChangeTileAt((GetPosition().y / TILE_HEIGHT), (GetPosition().x / TILE_WIDTH), -1);
			SetState(Actor::EDead);
		}
	}
	
}
