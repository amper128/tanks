#pragma once

#include <game/IObjectStatic.h>

class CObjectBrick : public IObjectStatic
{
public:
	CObjectBrick(CVector p = {0.0f, 0.0f, 0.0f});

	void collide(IObjectStatic *) { }
	void damage(float dmg1, float dmg2, float dmg3);
	std::string getClassName() { return "CObjectBrick"; }

	IObjectBase* clone() { return new CObjectBrick(); }

	~CObjectBrick();
};
