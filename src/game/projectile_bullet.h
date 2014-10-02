#pragma once

#include "rigid_body_dynamic.h"
#include "../graphics/tga.h"
#include "../graphics/graphics.h"

//-------------------------------------------------------------------------
//Класс для патрона
//-------------------------------------------------------------------------
class TBullet : public TRigidBodyDynamic
{
public:
	TBullet(Tpoint p, float angle, unsigned char type, unsigned char id);

	Tpoint getpos();
	float getangle();

	void collide(TRigidBodyStatic * coll);
	void step();
	void destroy();

	unsigned char pid();

	bool draw();

	~TBullet() {};

private:
	Tpoint position;
	float angle;
	float speed;

	unsigned char arm_dmg; //бронебойность
	unsigned char expl_dmg; //взрывность

	//кто хозяин-то?
	unsigned char player_id;
	int life_timer;
};
