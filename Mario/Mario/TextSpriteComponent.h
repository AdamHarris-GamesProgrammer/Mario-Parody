#pragma once
#include "SpriteComponent.h"
#include "SDL_ttf.h"

#include <iostream>
class TextSpriteComponent : public SpriteComponent
{
public:
	TextSpriteComponent(class Actor* owner, int updateOrder = 100);
	~TextSpriteComponent();

	TTF_Font* GetFont() const { return mFont; }
	SDL_Color GetTextColor() const { return mTextColor; }
	int GetTextSize() const { return mPointSize; }
	std::string GetText() const { return mText; }
	
	void SetFont(TTF_Font* newFont) { mFont = newFont; }
	void SetTextColor(SDL_Color newColor) { mTextColor = newColor; }
	void SetTextSize(int newSize);
	void SetText(std::string newText);
	void SetFontFilePath(std::string newPath) { mFilePath = newPath; }

private:
	TTF_Font* mFont;
	SDL_Color mTextColor;
	int mPointSize;
	std::string mText;
	std::string mFilePath;
};

