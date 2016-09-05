#pragma once

#include <game/CStaticRigidBody.h>

class CRigidBody : public CStaticRigidBody
{
private:
	CVector _speed;
	CVector _accel;
	float mass;

	float rot_speed;
	float rot_accel;
public:
	CRigidBody();

	~CRigidBody();
}
