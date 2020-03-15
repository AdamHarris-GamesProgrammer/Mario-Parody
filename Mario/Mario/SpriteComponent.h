#pragma once
#include "Component.h"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
	//(lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	//Virtual draw method allows derived components to change the functionality
	virtual void Draw(SDL_Renderer* renderer);
	
	//Sets the mTexture variable to the texture that's passed in
	virtual void SetTexture(SDL_Texture* texture);

	//Getter/Setter for the draw order
	int GetDrawOrder() const { return mDrawOrder; }
	void SetDrawOrder(int newValue) { mDrawOrder = newValue; }

	//Getters for the texture width and height
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }

	//Getters for the Dest and Source rect
	SDL_Rect* GetDestRect() const { return mDestRect; }
	SDL_Rect* GetSrcRect() const { return mSrcRect; }

	//Setters for the Source and Dest rect
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

