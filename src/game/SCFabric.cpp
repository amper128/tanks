#include <game/SCFabric.h>
#include <game/IObjectDynamic.h>

CFabric& CFabric::GetFabric()
{
	static CFabric _instance;
	return _instance;
}

IObjectBase* CFabric::CreateObject(string id)
{
	if (reg.find(id) != reg.end()) {
		IObjectBase* new_obj = reg[id]->clone();
		return new_obj;
	}
	return NULL;
}

IObjectBase* CFabric::CreateStatic(string id, CVector pos)
{
	if (IObjectStatic* obj = (IObjectStatic*)CreateObject(id))
	{
		obj->pos(pos);
		map->statics.push_back(obj);
		return obj;
	}
	return NULL;
}

IObjectBase* CFabric::CreateDynamic(string id, CVector pos)
{
	if (IObjectDynamic* obj = (IObjectDynamic*)CreateObject(id)) {
		map->dynamics.push_back(obj);
		obj->pos(pos);
		return obj;
	}
	return NULL;
}

void CFabric::setmap(CMap* level)
{
	map = level;
}
