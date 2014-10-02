#pragma once
#include "rigid_body_dynamic.h"

class TExplo : public TRigidBodyDynamic
{
public:
	TExplo(Tpoint pos, unsigned char dmg, unsigned char id);

	void step();
	void process() {};
	bool draw();
	void destroy() { _destroyed = true; };
	void collide(TRigidBodyStatic* body);

	~TExplo() {};
private:
	Tpoint position;
	float angle;

	unsigned int cur_dmg;
	unsigned int cur_size;
	int _tmr;
	float lightning;
};

class TExplo2 : public TRigidBodyDynamic
{
public:
	TExplo2(Tpoint pos, unsigned char dmg, unsigned char id);

	void step();
	void process() {};
	bool draw();
	void destroy() { _destroyed = true; };
	void collide(TRigidBodyStatic* body);

	~TExplo2() {};
private:
	Tpoint position;
	float angle;

	unsigned int cur_dmg;
	unsigned int cur_size;
	int _tmr;
	float lightning;
};

