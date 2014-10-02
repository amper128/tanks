#pragma once

class object_water : public TRigidBodyStatic
{
public:
	object_water(Tpoint pos);

	bool draw() { return true; };
	void destroy() { _destroyed = true; };
	void step() { };
	void collide(TRigidBodyStatic *coll) { };

	~object_water() {};
};
