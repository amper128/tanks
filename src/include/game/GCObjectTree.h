#pragma once

#include <game/IObjectStatic.h>

class CObjectTree : public IObjectStatic
{
public:
	CObjectTree(CVector pos = {0.0f, 0.0f, 0.0f});
	std::string getClassName() { return "CObjectTree"; }

	IObjectBase* clone() { return new CObjectTree(); }
	~CObjectTree() {}
};
