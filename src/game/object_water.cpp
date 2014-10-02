#include "object_water.h"

object_water::object_water(Tpoint pos)
{
	_type = oTypeWater;
	_pos = pos;
	_bounds = box(64,64);

//	std::string str;

//	str = "walls/brick.tga";
//	sprite = TexManager.load(str,point(0,0));
}
