#include "object_decal.h"

Tdecal::Tdecal(Tpoint pos, float angle, float alpha)
{
	_pos = pos;
	_angle = angle;
	_alpha = alpha;
}

void Tdecal::process()
{
	_alpha -= 0.0005;
	if (_alpha < 0)
		_destroyed = true;
}

Tdecal::~Tdecal()
{

}
