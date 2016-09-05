#include <game/IObject2D.h>

IObject2D::IObject2D()
{
	_destroyed = false;
	_pos = CVector(0.0f, 0.0f, 2.0f);
	_angle = 0;
	_alpha = 1;
	_size = {64, 64};
}

float IObject2D::alpha()
{
	return _alpha;
}

void IObject2D::alpha(float a)
{
	_alpha = a;
}

float IObject2D::angle()
{
	return _angle;
}

void IObject2D::angle(float a)
{
	_angle = a;
}

CVector IObject2D::pos()
{
	return _pos;
}

void IObject2D::pos(CVector p)
{
	if (p.z) {
		_pos = p;
	} else {
		_pos.x = p.x;
		_pos.y = p.y;
	}
}

CBox IObject2D::size()
{
	return _size;
}

void IObject2D::size(CBox s)
{
	_size = s;
}

IObject2D::~IObject2D()
{

}
