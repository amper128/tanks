#include <game/GCObjectWater.h>

CObjectWater::CObjectWater(CVector p)
{
	LoadConfig(getClassName());

	this->_size.w = 64;
	this->_size.h = 64;
	this->_pos = p;
}
