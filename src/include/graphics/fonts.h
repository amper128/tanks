#pragma once

#include <string>
#include <graphics/graphics.h>
#include <system/resource_manager.h>

class TFont
{
public:
	TFont();

	void LoadFont(std::string name);

	void DrawString(std::string text, float x, float y, TColor col = color(1.0f, 1.0f, 1.0f, 1.0f));
	void DrawStringCenter(std::string text, float x, float y, TColor col = color(1.0f, 1.0f, 1.0f, 1.0f));

	float StringWidth(std::string text);
	float StringHeight(std::string text);

	~TFont();

private:
	float xpos[256];
	float ypos[256];

	float chrw[256];
	float chrh[256];

	float yoffs[256];

	Sprite *fnt_sprite;
};
