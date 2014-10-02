#include "wall_beton.h"

TBetonWall::TBetonWall(Tpoint p)
{
	_pos.x = p.x;
	_pos.y = p.y;
	_bounds = box(64,64);
	_health = 100;

	std::string str;

	str = "walls/walls.tga";
	sprite = TexManager.load(str,point(0,0),4,4);

	sprite->frame = int(rand() % 4) + 8;
	//sprite->frame = 3;
}

TBetonWall::~TBetonWall()
{

}
