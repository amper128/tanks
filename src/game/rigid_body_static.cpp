#include "rigid_body_static.h"

TRigidBodyStatic::TRigidBodyStatic()
{
	_pos.x = 0.0f;
	_pos.y = 0.0f;
	_destroyed = false;
	_angle = 0.0f;
	_bounds = box(0,0);

	_fragility = 0.0f;
	_type = 0;
	_id = 0;
	_height = 0;
	_alpha = 1.0f;
}

TRigidBodyStatic::TRigidBodyStatic(float x, float y, float w, float h, float angle)
{
	_pos = point(x,y);

	_bounds = box(w,h);

	_destroyed = false;
}

TRigidBodyStatic::TRigidBodyStatic(Tpoint pos, Tbox b, float angle)
{
	_pos = pos;
	_bounds = b;

	_destroyed = false;
}

void TRigidBodyStatic::setpos(float x, float y)
{
	_pos.x = x;
	_pos.y = y;
}

void TRigidBodyStatic::setpos(Tpoint pos)
{
	_pos = pos;
}

Tpoint TRigidBodyStatic::pos()
{
	return _pos;
}

Tbox TRigidBodyStatic::bounds()
{
	return _bounds;
}

void TRigidBodyStatic::angle(float angle)
{
	_angle = angle;
}

float TRigidBodyStatic::angle()
{
	return _angle;
}

void TRigidBodyStatic::process()
{
	if (_angle > 360) _angle -=360;
	if (_angle < 0) _angle += 360;
}

TRigidBodyStatic::~TRigidBodyStatic()
{

}
