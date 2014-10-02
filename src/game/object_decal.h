#pragma once

#include "object_2d.h"

class Tdecal : public object_2d
{
public:
	Tdecal();
	Tdecal(Tpoint pos, float angle, float alpha = 1);

	void process();

	~Tdecal();
};
