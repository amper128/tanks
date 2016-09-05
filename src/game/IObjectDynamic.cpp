#include <game/IObjectDynamic.h>

IObjectDynamic::IObjectDynamic(CVector p, CBox b)
{
	this->_pos = p;
	this->_size = b;

	this->_speed = 0;
	this->_mass = 0;
	this->_maxspeed = 0;
	this->_accel = 0;
	this->_rot_speed = 0;
	this->_prev_pos = _pos;
	this->_prev_angle = 0;
}

float IObjectDynamic::speed()
{
	return this->_speed;
}

void IObjectDynamic::speed(float speed)
{
	this->_speed = speed;
}

float IObjectDynamic::rot_speed()
{
	return _rot_speed;
}

void IObjectDynamic::process()
{
	this->_prev_pos = this->_pos;
	this->_pos += CVector(_speed * Sin(-this->_angle), _speed * Cos(this->_angle));

	this->_prev_angle = this->_angle;
	this->_angle += this->_rot_speed;

	if (this->_angle > 360) this->_angle -=360;
	if (this->_angle < 0) this->_angle += 360;
}

void IObjectDynamic::prev_pos()
{
	this->_pos = this->_prev_pos;
	this->_angle = this->_prev_angle;
}

IObjectDynamic::~IObjectDynamic()
{

}
