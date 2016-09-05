#pragma once

#include "IProjectile.h"

//-------------------------------------------------------------------------
//Класс для патрона
//-------------------------------------------------------------------------
class CProjectileBullet : public IProjectile
{
public:
	CProjectileBullet(CVector p = {0.0f, 0.0f, 0.0f});

	void collide(IObjectStatic * coll);
	void step(void);

	bool draw(void);

	uint8_t pid(void);

	std::string getClassName(void) { return "CProjectileBullet"; }
	IObjectBase* clone(void) { return new CProjectileBullet(); }

private:
	uint32_t life_time;
	float tex_angle; //угол текстуры
};
