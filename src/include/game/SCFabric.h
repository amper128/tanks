#pragma once

#include <map>
#include <system/strings.h>
#include <game/IObjectBase.h>
#include <game/SCMap.h>

class CFabric
{
private:
	std::map<string,IObjectBase*> reg;
	CFabric() {}
	int current_id;
	CMap* map;

public:
	static CFabric& GetFabric();

	IObjectBase*	CreateObject(string id);
	IObjectBase*	CreateParticle(string id, CVector pos);
	IObjectBase*	CreateStatic(string id, CVector pos);
	IObjectBase*	CreateDynamic(string id, CVector pos);

	void setmap(CMap* level);

	template<typename T> void addPrototype(T* prototype)
	{
		string id = prototype->getClassName();
		reg[id] = prototype;
	}

	// Удаление прототипа из множества прототипов
	void removePrototype(string id)
	{
		reg.erase(reg.find(id));
	}
};
