#pragma once

#include <game/IObjectStatic.h>

class IObjectDynamic : public IObjectStatic
{
protected:
	float _speed;
	float _mass;
	float _maxspeed;
	float _accel;

	float _speed_angle;

	float _rot_speed;

	CVector _prev_pos;
	float _prev_angle;
public:
	IObjectDynamic(CVector pos = {0.0f, 0.0f, 0.0f}, CBox b = {64, 64});

	void speed(float speed);
	void setmaxspeed(float speed);
	float speed();
	float maxspeed();
	float rot_speed();

	void process();
	void prev_pos();

	~IObjectDynamic();
};
