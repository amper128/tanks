#pragma once

#include <vector>

class GUI_Widget
{
private:
	std::vector<GUI_Widget> childs;

protected:
	float _posx;
	float _posy;

	float _parx;
	float _pary;

	void set_parent_x(float x);
	void set_parent_y(float y);

public:
	virtual void draw() = 0;
};
