#pragma once

#include <map>
#include <system/strings.h>

class IObjectBase
{
private:

protected:
	string	_type;		//текстовое имя класса
	int	_id;		//глобальный id объекта (будет генериться фабрикой)

public:
	IObjectBase() { _type = "ObjectBase"; }

	virtual string getBaseClassName() { return _type; }
	virtual string getClassName() { return "ObjectBase"; }
	int id() { return _id; }
	virtual IObjectBase* clone() = 0;

	virtual void Serialize() {}
	virtual void DeSerialize() {}
	~IObjectBase() {}
};
