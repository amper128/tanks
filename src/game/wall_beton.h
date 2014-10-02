#pragma once

#include "rigid_body_static.h"
#include "../graphics/texture.h"

class TBetonWall : public TRigidBodyStatic
{
public:
	TBetonWall(Tpoint p = point(0,0));

	~TBetonWall();

	void step() { };
	void collide(TRigidBodyStatic *coll) { };
	void destroy() { _destroyed = true; };

	int wall_id;

private:
	float _health;
};
