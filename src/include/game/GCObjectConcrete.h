#pragma once

#include <game/IObjectStatic.h>

class CObjectConcrete : public IObjectStatic
{
public:
	CObjectConcrete(CVector p = {0.0f, 0.0f, 0.0f});
	std::string getClassName(void) { return "CObjectConcrete"; }
	IObjectBase* clone(void) { return new CObjectConcrete(); }

	~CObjectConcrete();
};
