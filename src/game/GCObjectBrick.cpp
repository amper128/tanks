#include <game/GCObjectBrick.h>

CObjectBrick::CObjectBrick(CVector p)
{
	_pos = p;

	LoadConfig(getClassName());
}

void CObjectBrick::damage(float dmg1, float dmg2, float dmg3)
{
	_health -= dmg1/3.0f;
	_health -= dmg2/5.0f;
	if (_health < 0)
		destroy();
	else if (_health < 12.5)
		sprite->frame = 7;
	else if (_health < 25)
		sprite->frame = 6;
	else if (_health < 37.5)
		sprite->frame = 5;
	else if (_health < 50)
		sprite->frame = 4;
	else if (_health < 62.5)
		sprite->frame = 3;
	else if (_health < 75)
		sprite->frame = 2;
	else if (_health < 87.5)
		sprite->frame = 1;
}

CObjectBrick::~CObjectBrick()
{

}
