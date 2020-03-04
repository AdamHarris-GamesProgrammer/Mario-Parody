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

	SDL_Rect* testDest;
	testDest = new SDL_Rect();

	testDest->w = GetTexWidth() * mOwner->GetScale();
	testDest->h = GetTexHeight() * mOwner->GetScale();

	testDest->x = mOwner->GetPosition().x;
	testDest->y = mOwner->GetPosition().y;

	mTexture = mOwner->GetGame()->GetEngine()->GetTextureFromFont(mFilePath, mPointSize, mText, mTextColor);
	SpriteComponent::SetTexture(mTexture);
}

TextSpriteComponent::~TextSpriteComponent()
{
	TTF_CloseFont(mFont);
	mFont = NULL;
	delete mFont;
}

void TextSpriteComponent::Draw(SDL_Renderer* renderer)
{
	SDL_Rect destRect;

	destRect.w = static_cast<int>(mTexWidth * mOwner->GetScale());
	destRect.h = static_cast<int>(mTexHeight * mOwner->GetScale());

	destRect.x = static_cast<int>(mOwner->GetPosition().x - destRect.w / 2);
	destRect.y = static_cast<int>(mOwner->GetPosition().y - destRect.h / 2);

	if (mTexture) {
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
	mTextColor = newColor;
	mTexture = mOwner->GetGame()->GetEngine()->GetTextureFromFont(mFilePath, mPointSize, mText, mTextColor);
}

void TextSpriteComponent::SetTextSize(int newSize)
{
	mPointSize = newSize;
	mTexture = mOwner->GetGame()->GetEngine()->GetTextureFromFont(mFilePath, mPointSize, mText, mTextColor);
	SpriteComponent::SetTexture(mTexture);
}

void TextSpriteComponent::SetText(std::string newText)
{
	mText = newText;
	mTexture = mOwner->GetGame()->GetEngine()->GetTextureFromFont(mFilePath, mPointSize, mText, mTextColor);
	SpriteComponent::SetTexture(mTexture);
}
