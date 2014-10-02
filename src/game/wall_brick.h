#pragma once

#include "rigid_body_static.h"
#include "../graphics/texture.h"

class TBrickWall : public TRigidBodyStatic
{
public:
	TBrickWall(Tpoint p = point(0,0));

	~TBrickWall();

	void step() { };
	void collide(TRigidBodyStatic *coll) { };
	void destroy() { _destroyed = true; };
	void damage(float dmg1, float dmg2);

	int wall_id;
};
