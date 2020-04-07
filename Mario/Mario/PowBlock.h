#pragma once
#include "Tile.h"
class PowBlock : public Tile
{
public:
	PowBlock(class Game* game, SDL_Rect* srcRect, SDL_Rect* destRect);
	~PowBlock();

	//Getter/Setter for bActive
	bool GetActive() const { return bActive; }
	bool SetActive(bool newValue) { bActive = newValue; }

	//Takes damage from the pow block (Determines. the src rect and if the object has been destroyed)
	void TakeDamage();
private:
	const int mNumberOfSprites = 4;

	bool bActive = true;
	int healthLeft = 3;
};

