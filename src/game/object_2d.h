#pragma once
#include "../system/vectors.h"
#include "../graphics/graphics.h"

#include "baseobject.h"

//class object_2d : public BaseObj
class object_2d
{
protected:
	Tpoint _pos;
	float _angle;
	bool _destroyed;
	float _alpha;
	Tbox _size;

	float _height;
public:
	object_2d();

	Tpoint pos();
	Tbox size();
	float angle();
	float height() { return _height; };

	virtual bool draw() { return false; };
	virtual void process() = 0;

	Sprite* sprite;

	virtual bool destroyed() { return _destroyed; };
	float alpha() { return _alpha; };

	~object_2d() {};
};
