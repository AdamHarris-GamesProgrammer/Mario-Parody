#include "TextSpriteComponent.h"
#include "Actor.h"
#include "Game.h"

TextSpriteComponent::TextSpriteComponent(class Actor* owner, int updateOrder /*= 100*/) :
	SpriteComponent(owner, updateOrder),
	mPointSize(24),
	mText("No text found"),
	mFilePath("Assets/Fonts/Free Shaped Corner/Shaped Corner-Basic.ttf")
{

	SDL_Color defaultColor = SDL_Color();
	defaultColor = { 255,255,255,255 };
	mTextColor = defaultColor;

	mTexture = mOwner->GetGame()->GetTextureFromFont(mFilePath, mPointSize, mText, mTextColor);
	SpriteComponent::SetTexture(mTexture);
}

TextSpriteComponent::~TextSpriteComponent()
{

}

void TextSpriteComponent::SetTextSize(int newSize)
{
	mPointSize = newSize;
	mTexture = mOwner->GetGame()->GetTextureFromFont(mFilePath, mPointSize, mText, mTextColor);
	SpriteComponent::SetTexture(mTexture);
}

void TextSpriteComponent::SetText(std::string newText)
{
	mText = newText;
	mTexture = mOwner->GetGame()->GetTextureFromFont(mFilePath, mPointSize, newText, mTextColor);
	SpriteComponent::SetTexture(mTexture);
}
