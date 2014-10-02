#include "rigid_body_dynamic.h"

TRigidBodyDynamic::TRigidBodyDynamic()
{
	_pos = point(0,0);
	_speed = 0;
	_mass = 0;
	_maxspeed = 0;
	_accel = 0;
	_rot_speed = 0;
	_prev_pos = _pos;
	_prev_angle = 0;
}

TRigidBodyDynamic::TRigidBodyDynamic(float x, float y, float w, float h)
{
	_pos.x = x;
	_pos.y = y;

	_bounds.w = w;
	_bounds.h = h;
}

TRigidBodyDynamic::TRigidBodyDynamic(Tpoint pos, Tbox b)
{
	_pos = pos;
	_bounds = b;
}

float TRigidBodyDynamic::speed()
{
	return _speed;
}

float TRigidBodyDynamic::rot_speed()
{
	return _rot_speed;
}

void TRigidBodyDynamic::setspeed(float speed)
{
	_speed = speed;
}

void TRigidBodyDynamic::process()
{
	_prev_pos = _pos;
	_pos.x += _speed*Sin(-_angle);
	_pos.y += _speed*Cos(_angle);

	_prev_angle = _angle;
	_angle += _rot_speed;

	if (_angle > 360) _angle -=360;
	if (_angle < 0) _angle += 360;
}

void TRigidBodyDynamic::prev_pos()
{
	_pos = _prev_pos;
	_angle = _prev_angle;
}

TRigidBodyDynamic::~TRigidBodyDynamic()
{

}
