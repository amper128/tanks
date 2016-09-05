#include <gui/label.h>

GUI_Label::GUI_Label(float x, float y)
{
	_posx = x;
	_posy = y;
	_font = NULL;
	_text = "";
	_color = color(0,0,0,1);
}

void GUI_Label::setfont(TFont* font)
{
	_font = font;
}

void GUI_Label::settext(std::string text)
{
	_text = text;
}

void GUI_Label::setcolor(TColor color)
{
	_color = color;
}

void GUI_Label::draw()
{
	if (_font != NULL) {
		_font->DrawString(_text,_posx+_parx,_posy+_pary,_color);
	}
}

GUI_Label::~GUI_Label()
{

}
