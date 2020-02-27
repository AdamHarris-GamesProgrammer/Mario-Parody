#pragma once
#include "Tile.h"
class PowBlock : public Tile
{
public:
	PowBlock(class Game* game, SDL_Rect* srcRect, SDL_Rect* destRect);
	~PowBlock();

	bool GetActive() const { return bActive; }
	bool SetActive(bool newValue) { bActive = newValue; }

	void TakeDamage();
private:
	bool bActive = true;
	int healthLeft = 3;
};

