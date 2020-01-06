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

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }

protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};

