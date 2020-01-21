#pragma once
#include "Component.h"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
	//(lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	void SetDrawOrder(int newValue) { mDrawOrder = newValue; }

	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }
	SDL_Rect* GetDestRect() const { return mDestRect; }
	SDL_Rect* GetSrcRect() const { return mSrcRect; }

	void SetSrcRect(SDL_Rect* newRect) { mSrcRect = newRect; }
	void SetDestRect(SDL_Rect* newRect) { mDestRect = newRect; }

protected:
	SDL_Texture* mTexture;
	SDL_Rect* mDestRect;
	SDL_Rect* mSrcRect;

	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};

