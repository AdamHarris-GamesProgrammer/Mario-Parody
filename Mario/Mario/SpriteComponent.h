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
	virtual void Draw(SDL_Renderer* renderer, SDL_Rect* sourceRect, double rotation = 0.0f, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	virtual void Draw(SDL_Renderer* renderer, SDL_Rect* sourceRect, SDL_Rect* destRect);
	virtual void SetTexture(SDL_Texture* texture);
	virtual void Draw(SDL_Renderer* renderer, SDL_Rect* destRect);

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

