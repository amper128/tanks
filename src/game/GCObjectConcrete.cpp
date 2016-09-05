#include <game/GCObjectConcrete.h>

CObjectConcrete::CObjectConcrete(CVector p)
{
	LoadConfig(getClassName());

	sprite->frame = int(rand() % 4) + 8;

	_pos = p;
}

CObjectConcrete::~CObjectConcrete()
{

}
