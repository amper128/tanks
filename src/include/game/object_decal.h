#pragma once

#include <game/IObject2D.h>

class Tdecal : public IObject2D
{
public:
	Tdecal();
	Tdecal(CVector pos, float angle, float alpha = 1);

	void process();
	std::string getClassName() { return "CObjectDecal"; }
	IObjectBase* clone() { printf("clone water\n"); return new Tdecal(*this); }

	~Tdecal();
};
