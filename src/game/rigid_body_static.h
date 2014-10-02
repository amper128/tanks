#pragma once
#include "../system/vectors.h"
#include "../graphics/graphics.h"
#include "constants.h"
#include "baseobject.h"

class TRigidBodyStatic : public BaseObj
{
protected:
	float _angle;
	Tpoint _pos;
	Tbox _bounds;

	bool _destroyed;	//объект был уничтожен (для последующего удаления из списка)
	int _id;		//глобальный id объекта (а хз, надо ли)

	int _type;

	float _fragility;	//разбиваемость. от 0 до 1. если 0 - значит неразбиваемый, 1 - ломается от любого чиха

	float _height;
	float _alpha;
	float _health;
public:
	TRigidBodyStatic();
	TRigidBodyStatic(float x, float y, float w, float h, float angle=0.0f);
	TRigidBodyStatic(Tpoint pos, Tbox b, float angle=0.0f);

	void setpos(float x, float y);
	void setpos(Tpoint pos);
	Tpoint pos();

	float angle();
	void angle(float angle);

	Tbox bounds(); //размеры (прямоугольные)

	void process();

	float height() { return _height; };
	float alpha() { return _alpha; };

	virtual void collide(TRigidBodyStatic * coll) = 0;
	virtual void step() = 0;
	virtual void destroy() { _destroyed = true; };
	virtual void damage(float dmg1, float dmg2) { };

	virtual bool draw() { return false; };

	int id() { return _id; };
	bool destroyed() { return _destroyed; };

	int gettype() { return _type; };

	Sprite *sprite;

	~TRigidBodyStatic();
};
