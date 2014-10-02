#include "map.h"
#include <cstdio>
#include <iostream>
#include "../global.h"

Tmap::Tmap()
{

}

void Tmap::step_objects()
{
	if (!decals.empty())
	{
		std::list<object_2d*>::iterator element, end;
		object_2d *dec;
		element = decals.begin ();
		end = decals.end();
		while (element != end)
		{
			(*element)->process();
			if ((*element)->destroyed())
			{
				delete (*element);
				decals.erase(element++);
			}
			element++;
		
		}
	}

	if (!statics.empty())
	{
		std::list<TRigidBodyStatic*>::iterator element, end;
		element = statics.begin ();
		end = statics.end ();
		while (element != end)
		{
			(*element)->step();
			if ((*element)->destroyed())
			{
				delete (*element);
				statics.erase(element++);
			}
			element++;
		}
	}

	if (!dynamics.empty())
	{
		std::list<TRigidBodyDynamic*>::iterator element, end;
		TRigidBodyDynamic* body;
		element = dynamics.begin ();
		end = dynamics.end ();
		do
		{
			body = (*element);
			body->step();
			//if (fabs(body->speed()) > 0 || fabs(body->rot_speed()) > 0)
			{
				std::list<TRigidBodyDynamic*>::iterator coll_el, coll_end;

				//TODO: иптить нагорожено... над оптимизировать
				TRigidBodyDynamic* coll_body;

				coll_el = dynamics.begin ();
				coll_end = dynamics.end ();
				do
				{
					coll_body = (*coll_el);
					if (coll_el != element)
					if (DistanceBetweenPoints(body->pos(),coll_body->pos()) <= 256)
					{
						//printf("Checking collision with %.2f:%.2f (%.2f x %.2f) ",body->pos().x, body->pos().y, body->bounds().w, body->bounds().h);
						//printf("and %.2f:%.2f (%.2f x %.2f)\n",coll_body->pos().x,coll_body->pos().y,coll_body->bounds().w,coll_body->bounds().h);
						if (colliderectA(body->pos(),body->bounds(),body->angle(),coll_body->pos(),coll_body->bounds(),coll_body->angle()))
						{
							//body->collide(coll_body);
						}
					}
					coll_el++;
				}
				while (coll_el != coll_end);

				std::list<TRigidBodyStatic*>::iterator coll_el_s, coll_end_s;

				TRigidBodyStatic* coll_body_s;

				coll_el_s = statics.begin ();
				coll_end_s = statics.end ();
				do
				{
					coll_body_s = (*coll_el_s);
					if (DistanceBetweenPoints(body->pos(),coll_body_s->pos()) <= 256)
					{
						//printf("Checking collision with %.2f:%.2f (%.2f x %.2f) ",body->pos().x, body->pos().y, body->bounds().w, body->bounds().h);
						//printf("and %.2f:%.2f (%.2f x %.2f)\n",coll_body_s->pos().x,coll_body_s->pos().y,coll_body_s->bounds().w,coll_body_s->bounds().h);
						if (colliderectA(body->pos(),body->bounds(),body->angle(),coll_body_s->pos(),coll_body_s->bounds(),coll_body_s->angle()))
						{
							body->collide(coll_body_s);
						}
					}
					coll_el_s++;
				}
				while (coll_el_s != coll_end_s);
			}

			if (body->destroyed())
			{
				delete (*element);
				dynamics.erase(element++);
			}
			element++;
		}
		while (element != end);
	}
}

//void Tmap::add_rigid(TRigidBody body)
//{
//	objects.add(body);
//}

void Tmap::loadmap(string name)
{
	FILE *mapfile;
	if (mapfile = fopen(("gamedata/maps/"+name+".map").c_str(),"r"))
	//if (mapfile = fopen("gamedata/maps/level02.map","r"))
	{
		int r;

		int lens;
		r = fread(&lens,4,1,mapfile);
		printf("len - %i\n",lens);
		char *MapName = new char[lens];
		r = fread(MapName,lens,1,mapfile);
		std::cout << MapName << "\n";

		r = fread(&width,2,1,mapfile);
		r = fread(&height,2,1,mapfile);
		width = width*2+64;
		height = height*2+64;
		printf("map - %i:%i\n",width,height);

		int cx,cy;
		cx = width/64+2;
		cy = height/64+2;
		map = new char*[cx+2];
		for (int i=0; i<cx+2;i++)
		{
			map[i] = new char[cy+2];
			for (int j=0; j<cy+2; j++)
			{
				map[i][j] = 0;
			}
		}
		printf("level - %i:%i\n",cx,cy);

		for (int i = 0; i < cx-1; i++)
		{
			add_object(i*64,height,1);
			add_object(i*64,0,1);
		}

		for (int i = 0; i < cy-1; i++)
		{
			add_object(0,i*64,1);
			add_object(width,i*64,1);
		}

		int objnum;
		r = fread(&objnum,sizeof(objnum),1,mapfile);
		printf("objects - %i\n",objnum);

		char objtype;
		short _x,_y;
		for (int i=0; i<objnum;i++)
		{
			r = fread(&objtype,sizeof(objtype),1,mapfile);
			r = fread(&_x,2,1,mapfile);
			r = fread(&_y,2,1,mapfile);

			add_object(_x*2+64,height-_y*2-64,objtype);
		}

		fclose(mapfile);
	}
}

void Tmap::add_object(float x, float y, char type)
{
	//TStaticObject *obj = new TStaticObject;	
	//obj->pos = point(x,y);
	//obj->type = type;

	//statics.push_back(obj);
	switch (type)
	{
	case oWallBrick:
		TBrickWall *brick;
		brick = new TBrickWall(point(x,y));
		statics.push_back(brick);
		break;
	case oWallBeton:
		TBetonWall *beton;
		beton = new TBetonWall(point(x,y));
		statics.push_back(beton);
		break;
	case oTree:
		object_tree *tree;
		tree = new object_tree(point(x,y));
		objects_2d.push_back(tree);
		break;
	case oWater:
//		int cy = height/64+2;
		int m_x, m_y;
		m_x = x/64+1;
		m_y = y/64;
		map[m_x][m_y] = 15;

		object_water *water;
		water = new object_water(point(x,y));
		statics.push_back(water);
		break;
	}
}

Tmap::~Tmap()
{

}
