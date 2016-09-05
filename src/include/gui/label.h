#pragma once

#include "widget.h"
#include "../graphics/fonts.h"

class GUI_Label : public GUI_Widget
{
private:
	std::string _text;
	TFont* _font;
	TColor _color;

public:
	GUI_Label(float x=0, float y=0);
	void setfont(TFont* font);
	void setcolor(TColor color);
	void settext(std::string text);

	void draw();

	~GUI_Label();
};
