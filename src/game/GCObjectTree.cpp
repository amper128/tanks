#include <game/GCObjectTree.h>

CObjectTree::CObjectTree(CVector p)
{
	LoadConfig(getClassName());

	pos(p);

	_pos.z = _pos.z + rand()/(RAND_MAX/32);
}
