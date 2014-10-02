#pragma once
#include "rigid_body_static.h"

class TRigidBodyDynamic : public TRigidBodyStatic
{
protected:
	float _speed;
	float _mass;
	float _maxspeed;
	float _accel;

	float _rot_speed;

	Tpoint _prev_pos;
	float _prev_angle;
public:
	TRigidBodyDynamic();
	TRigidBodyDynamic(float x, float y, float w, float h);
	TRigidBodyDynamic(Tpoint pos, Tbox b);

	void setspeed(float speed);
	void setmaxspeed(float speed);
	float speed();
	float maxspeed();
	float rot_speed();

//	virtual void collide(TRigidBodyDynamic * coll) = 0;
//	virtual void collide(TRigidBodyStatic * coll) = 0;

	void process();
	void prev_pos();

	~TRigidBodyDynamic();
};
