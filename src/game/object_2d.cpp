#include "object_2d.h"

object_2d::object_2d()
{
	_destroyed = false;
	_pos = point(0,0);
	_angle = 0;
	_alpha = 1;
	_size = box(64,64);
	_height = 0;
}

Tpoint object_2d::pos()
{
	return _pos;
}

float object_2d::angle()
{
	return _angle;
}

Tbox object_2d::size()
{
	return _size;
}

//object_2d::~object_2d()
//{
//
//}
