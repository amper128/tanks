#pragma once

#include <game/IProjectile.h>

//-------------------------------------------------------------------------
//Класс для патрона
//-------------------------------------------------------------------------
class CProjectileFire : public IProjectile
{
public:
	CProjectileFire(CVector p = {0.0f, 0.0f, 0.0f});

	void collide(IObjectStatic * coll);
	void step(void);

	bool draw(void);

	std::string getClassName(void) { return "CProjectileFire"; }
	IObjectBase* clone(void) { return new CProjectileFire(); }

	~CProjectileFire() {}

private:
	uint32_t life_time;
	uint32_t fire_time;
	uint32_t _tmr;
	uint32_t _act;
	float tex_angle; //угол текстуры
};
