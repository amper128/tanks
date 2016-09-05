#pragma once

#include <list>
#include "IObject2D.h"
#include "IObjectStatic.h"
#include "IObjectDynamic.h"

class CGrid
{
private:
	int width;
	int height;

	float cell_w;
	float cell_h;

	struct o_list
	{
		std::list<IObject2D*> particles;
		std::list<IObjectStatic*> statics;
		std::list<IObjectDynamic*> dynamics;
	};

	o_list* cells;
public:
	CGrid(int w, int h, float cw=256.0f, float ch=256.0f);

	

	~CGrid();
};
