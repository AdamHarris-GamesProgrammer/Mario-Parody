#include "TextSpriteComponent.h"
#include "Actor.h"
#include "Game.h"

TextSpriteComponent::TextSpriteComponent(class Actor* owner, int updateOrder /*= 100*/) :
	SpriteComponent(owner, updateOrder),
	mPointSize(24),
	mText("No text found"),
	mFilePath("Assets/Fonts/Free Shaped Corner/Shaped Corner-Basic.ttf") //Sets default values to sensible values
{

	//Sets the default colour to white
	SDL_Color defaultColor = SDL_Color();
	defaultColor = { 255,255,255,255 };
	mTextColor = defaultColor;

	//Sets the texture
	mTexture = mOwner->GetGame()->GetEngine()->GetTextureFromFont(mFilePath, mPointSize, mText, mTextColor);
	SpriteComponent::SetTexture(mTexture);
}

TextSpriteComponent::~TextSpriteComponent()
{
	//Deletes the font 
	TTF_CloseFont(mFont);
	mFont = NULL;
	delete mFont;
}

void TextSpriteComponent::Draw(SDL_Renderer* renderer)
{
	SDL_Rect destRect;

	destRect.w = static_cast<int>(mTexWidth * mOwner->GetScale());
	destRect.h = static_cast<int>(mTexHeight * mOwner->GetScale());

	//Sets the position to be the middle of the owners dest rect
	destRect.x = static_cast<int>(mOwner->GetPosition().x - destRect.w / 2);
	destRect.y = static_cast<int>(mOwner->GetPosition().y - destRect.h / 2);

	//if a texture is found
	if (mTexture) {
		//render the text
		SDL_RenderCopyEx(renderer,
			mTexture,
			nullptr,
			&destRect,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE);
	}
}

void TextSpriteComponent::SetTextColor(SDL_Color newColor)
{
	//Sets the text color
	mTextColor = newColor;

	//reloads the text with the new color
	mTexture = mOwner->GetGame()->GetEngine()->GetTextureFromFont(mFilePath, mPointSize, mText, mTextColor);
}

void TextSpriteComponent::SetTextSize(int newSize)
{
	//sets the texture size
	mPointSize = newSize;

	//reloads the font with the new font size
	mTexture = mOwner->GetGame()->GetEngine()->GetTextureFromFont(mFilePath, mPointSize, mText, mTextColor);
	
	//Sets the texture
	SpriteComponent::SetTexture(mTexture);
}

void TextSpriteComponent::SetText(std::string newText)
{
	//sets the text member variable equal to the new text
	mText = newText;
	
	//reloads the font with the new text
	mTexture = mOwner->GetGame()->GetEngine()->GetTextureFromFont(mFilePath, mPointSize, mText, mTextColor);

	//Sets the texture
	SpriteComponent::SetTexture(mTexture);
}
