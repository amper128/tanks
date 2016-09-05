#pragma once

#include <system/xmlParser.h>
#include <game/IObject2D.h>
#include <system/strings.h>

class IObjectStatic : public IObject2D
{
protected:
	float _fragility;	//разбиваемость. от 0 до 100. если 0 - значит неразбиваемый, 100 - ломается от любого чиха
	float _health;		//живучесть

public:
	static CXMLConfig* config;

	IObjectStatic();
	IObjectStatic(CVector pos, CBox b);

	void setpos(CVector pos);

	void process(void);

	bool	solid;
	bool	flat;

	virtual void collide(IObjectStatic * coll) {}
	virtual void step(void) {}
	virtual void destroy(void) { _destroyed = true; }
	virtual void damage(float dmg1 = 0, float dmg2 = 0, float dmg3 = 0) {}
	std::string getClassName(void) { return "CObjectStatic"; }

	virtual void LoadConfig(string name);

	bool checkCollide(IObjectStatic * coll);

	virtual string gettype(void) { return getClassName(); }

	~IObjectStatic();
};
