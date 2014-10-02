#pragma once
#include <list>
#include "../system/vectors.h"
#include "object_defs.h"


class Tmap
{
public:
	Tmap();

	char **map;
	void loadmap(string name);

	std::list<object_2d*> decals;
	std::list<object_2d*> objects_2d;
	std::list<TRigidBodyStatic*> statics;
	std::list<TRigidBodyDynamic*> dynamics;
//	std::list<object_2d*> objects_2d_tl;	//top layer (trees, etc)

	//std::list<TStaticObject*> statics;
	
	//void add_trac(Tpoint pos, float angle);
	//void add_rigid(TRigidBody body);

	void step_objects();
	void add_object(float x, float y, char type);

	int width;
	int height;

	~Tmap();

	
} MAP;
