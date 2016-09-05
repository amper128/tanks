#include <game/object_decal.h>

Tdecal::Tdecal(CVector p, float an, float alpha)
{
	pos(p);
	angle(an);
	_alpha = alpha;
}

void Tdecal::process()
{
	_alpha -= 0.0005;
	if (_alpha < 0)
		destroy();
}

Tdecal::~Tdecal()
{

}
