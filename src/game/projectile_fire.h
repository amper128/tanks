#pragma once

#include "rigid_body_dynamic.h"
#include "../graphics/tga.h"
#include "../graphics/graphics.h"

//-------------------------------------------------------------------------
//Класс для патрона
//-------------------------------------------------------------------------
class TProjectileFire : public TRigidBodyDynamic
{
public:
	TProjectileFire(Tpoint p, float angle, unsigned char type, unsigned char id);

	Tpoint getpos();
	float getangle();

	void collide(TRigidBodyStatic * coll);
	void step();
	void destroy();

	unsigned char pid();

	bool draw();

	~TProjectileFire() {};

private:
	unsigned char arm_dmg; //бронебойность
	unsigned char expl_dmg; //взрывность
	unsigned char fire_dmg; //поджигательность

	//кто хозяин-то?
	unsigned char player_id;
	int life_time;
	int fire_time;
	unsigned char _tmr;
	unsigned char _act;
	float _angle2; //угол текстуры
};
