#pragma once

#include <system/vectors.h>

class CStaticRigidBody
{
private:
	float _angle;
	bool _solid;
	bool _flat;
	CVector _pos;

	CPoly*  bounds;
public:

	CStaticRigidBody(CVector pos = {0.0f, 0.0f, 0.0f}, float angle = 0.0f, bool solid = true, bool flat = false);

	void set_poly(CPoly* poly);

	bool collide(const CStaticRigidBody& coll);
	void setpos(const CVector& pos);
	CVector pos(void);

	void rotate(float angle);
	float angle(void);

	~CStaticRigidBody();
};
