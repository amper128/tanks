#pragma once

#include <game/IObjectStatic.h>

class CObjectWater : public IObjectStatic
{
public:
	CObjectWater(CVector pos = {0.0f, 0.0f, 0.0f});

	bool draw(void) { return true; }

	std::string getClassName(void) { return "CObjectWater"; }
	IObjectBase* clone(void) { return new CObjectWater(); }

	~CObjectWater() {}
};
