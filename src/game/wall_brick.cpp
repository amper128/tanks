#include "wall_brick.h"

TBrickWall::TBrickWall(Tpoint p)
{
	_pos.x = p.x;
	_pos.y = p.y;
	_bounds = box(64,64);
	_health = 100;

	std::string str;

	str = "walls/walls.tga";
	sprite = TexManager.load(str,point(0,0),4,4);
	sprite->frame = 4;
}

void TBrickWall::damage(float dmg1, float dmg2)
{
	_health -= dmg1/2;
	_health -= dmg2;
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

TBrickWall::~TBrickWall()
{

}
