#include "object_tree.h"

object_tree::object_tree(Tpoint pos)
{
	_pos = pos;
	_size = box(192,192);

	std::string str;

	str = "objects/tree.tga";
	sprite = TexManager.load(str,point(0,0));
	sprite->part_texture = false;

	_height = 100;
}

bool object_tree::draw()
{
	//draw_texture(sprite,_pos,_angle);
	return false;
}
