#include <game/SCMap.h>
#include <game/SCFabric.h>

#include <game/GCObjectConcrete.h>
#include <game/GCObjectBrick.h>
#include <game/GCObjectTree.h>
#include <game/GCObjectWater.h>

CMap::CMap()
{
	grounds = new Texture[16];

	grounds[0] = LoadSpr("gamedata/textures/grounds/ground.tga");
	grounds[1] = LoadSpr("gamedata/textures/grounds/grass.tga");
	grounds[2] = LoadSpr("gamedata/textures/grounds/grass2.tga");

	grounds[8] = LoadSpr("gamedata/textures/grounds/snowy_ground1.tga");
	grounds[9] = LoadSpr("gamedata/textures/grounds/snowy_ground2.tga");
	grounds[10] = LoadSpr("gamedata/textures/grounds/snow1.tga");
	grounds[11] = LoadSpr("gamedata/textures/grounds/snow2.tga");
	grounds[12] = LoadSpr("gamedata/textures/grounds/ice.tga");
	grounds[13] = LoadSpr("gamedata/textures/grounds/sand1.tga");
	grounds[14] = LoadSpr("gamedata/textures/grounds/sand2.tga");
	grounds[15] = LoadSpr("gamedata/textures/grounds/water.tga");
}

void CMap::step_objects()
{
	uint32_t i, j;

	if (!particles.empty()) {
		std::list<IObject2D*>::iterator element, end;

		end = particles.end();

		for (element = particles.begin(); element != end; element++) {
			(*element)->process();

			if ((*element)->destroyed()) {
				delete (*element);
				//element = particles.erase(element);
			}
		}
	}

	{
		std::list<IObjectStatic*>::iterator element, end;

		for (i = 0; i < cells_x; i++) {
			for (j = 0; j < cells_y; j++) {
				if (!cells[i][j].statics.empty()) {
					element = cells[i][j].statics.begin();
					end = cells[i][j].statics.end();

					while (element != end) {
						(*element)->step();
						if ((*element)->destroyed()) {
							delete (*element);
							cells[i][j].statics.erase(element++);
						}
						element++;
					}
				}
			}
		}
	}

	if (!dynamics.empty()) {
		std::list<IObjectDynamic*>::iterator element, end;
		IObjectDynamic* body;

		std::list<IObjectDynamic*>::iterator coll_el, coll_end;
		IObjectDynamic* coll_body;

		std::list<IObjectStatic*>::iterator coll_el_s, coll_end_s;
		IObjectStatic* coll_body_s;

		element = dynamics.begin();
		end = dynamics.end();

		do {
			body = (*element);
			body->process();
			body->step();

			coll_el = dynamics.begin ();
			coll_end = dynamics.end ();

			do {
				coll_body = (*coll_el);
				if (coll_el != element) {
					if (DistanceBetweenPoints(body->pos(), coll_body->pos()) <= 256 && coll_body->solid) {
						if (body->checkCollide(coll_body)) {
							std::cout << "collide bodies\n" << std::flush;
							body->collide(coll_body);
						}
					}
				}
				coll_el++;
			} while (coll_el != coll_end);

			for (i = max(0u, uint32_t(body->pos().x + 64) / 128 - 1u); i < min(uint32_t(body->pos().x + 64) / 128 + 2, cells_x); i++) {
				for (j = max(0u, uint32_t(body->pos().y + 64) / 128 - 1u); j < min(uint32_t(body->pos().y + 64) / 128 + 2, cells_y); j++) {
					coll_el_s = cells[i][j].statics.begin ();
					coll_end_s = cells[i][j].statics.end ();

					do {
						coll_body_s = (*coll_el_s);
						if (body->checkCollide(coll_body_s)) {
							std::cout << "collide static bodies\n" << std::flush;
							body->collide(coll_body_s);
						}
						coll_el_s++;
					} while (coll_el_s != coll_end_s);
				}
			}

			if (body->destroyed()) {
				delete (*element);
				dynamics.erase(element++);
			}
			element++;
		} while (element != end);
	}
}

void CMap::loadmap(string name)
{
	FILE *mapfile;

	std::cout << "Loading map\n";

	if ((mapfile = fopen(string("gamedata/maps/"+name+".map").c_str(),"r")) != NULL) {
		CFabric& fabric = CFabric::GetFabric();
		enum object_types obj_type;
		uint8_t tmp_type;

		int r;
		uint32_t i, j;
		uint32_t lens;
		char * MapName;
		uint16_t w, h;
		uint32_t cx, cy;

		uint32_t objnum;
		uint16_t _x,_y;

		r = fread(&lens, sizeof(lens), 1, mapfile);
		if (r < 1) {
			exit(1);
		}

		printf("len - %i\n", lens);

		MapName = new char[lens + 1];
		r = fread(MapName, lens, 1, mapfile);
		if (r < 1) {
			exit(1);
		}

		MapName[lens] = '\0';
		std::cout << MapName << "\n";

		r = fread(&w, sizeof(w), 1, mapfile);
		r = fread(&h, sizeof(h), 1, mapfile);

		map_w = w * 2 + 64;
		map_h = h * 2 + 64;

		printf("map - %.2f:%.2f\n", map_w, map_h);

		cx = map_w / 64 + 1;
		cy = map_h / 64 + 1;

		cells_x = map_w / 128 + 2;
		cells_y = map_h / 128 + 2;

		cells = new CCell*[cells_x + 1];
		for (i = 0; i <= cells_x; i++) {
			cells[i] = new CCell[cells_y + 1];
		}

		printf("level size: %ix%i\n", cells_x, cells_y);

		landscape = new uint8_t* [cx + 1];
		for (i = 0; i < cx + 1; i++) {
			landscape[i] = new uint8_t[cy + 1];
			for (j = 0; j < cy + 1; j++) {
				landscape[i][j] = 0;
			}
		}
		printf("landscape size: %ix%i\n",cx,cy);

		fabric.addPrototype(new CObjectBrick());
		fabric.addPrototype(new CObjectConcrete());
		fabric.addPrototype(new CObjectTree());
		fabric.addPrototype(new CObjectWater());
		//fabric.addPrototype(new CProjectileFire());
		//fabric.addPrototype(new CProjectileBullet());

		for (i = 0; i < cx; i++) {
			add_object(i * 64, map_h, oTypeWallConcrete);
			add_object(i * 64, 0, oTypeWallConcrete);
		}

		for (i = 0; i < cy - 1; i++) {
			add_object(map_w, i * 64, oTypeWallConcrete);
			add_object(0, i * 64, oTypeWallConcrete);
		}

		r = fread(&objnum, sizeof(objnum), 1, mapfile);
		printf("objects - %i\n", objnum);

		for (i = 0; i < objnum; i++) {
			//r = fread(&obj_type, sizeof(obj_type), 1, mapfile);
			r = fread(&tmp_type, 1, 1, mapfile);
			obj_type = (enum object_types)tmp_type;
			r = fread(&_x, 2, 1, mapfile);
			r = fread(&_y, 2, 1, mapfile);
			add_object(_x * 2 + 64, map_h - _y * 2 - 64, obj_type);
		}

		fclose(mapfile);
	} else {
		exit(1);
	}
}

void CMap::add_object(float x, float y, enum object_types type)
{
	CFabric& fabric = CFabric::GetFabric();
	IObjectStatic* st;
	string obj_type;
	int cx, cy;

	switch (type) {
	case oTypeWallConcrete:
		obj_type = "CObjectConcrete";
		break;

	case oTypeWallBrick:
		obj_type = "CObjectBrick";;
		break;

	case oTypeTree:
		obj_type = "CObjectTree";
		break;

	case oTypeWater:
		int m_x, m_y;
		m_x = x / 64;
		m_y = y / 64;
		landscape[m_x][m_y] = 15;

		obj_type = "CObjectWater";
		break;

	default:
		break;
	}

	st = (IObjectStatic*)fabric.CreateObject(obj_type);
	if (st) {
		st->pos({x, y, 0.0f});

		cx = (int)(x + 64) / 128;
		cy = (int)(y + 64) / 128;

		cells[cx][cy].statics.push_back(st);
	}
}

void CMap::DrawObjects()
{
	CRenderManager& render = CRenderManager::GetInstance();
	CPoint ViewPos = render.ViewPort();
	CBox ViewSize = render.ViewSize();
	std::list<IObjectStatic*>::iterator element, end;
	IObjectStatic* obj;

	int i, j;

	for (i = max(0, int(ViewPos.x / 128 - ViewSize.w / 256));
	     i < min(int(ViewPos.x / 128 + ViewSize.w / 256) + 2, (int)cells_x); i++)
	{
		for (j = max(0, int(ViewPos.y / 128) - 4); j < min(int(ViewPos.y / 128) + 6, (int)cells_y); j++) {
			if (!cells[i][j].statics.empty()) {
				end = cells[i][j].statics.end();
				for (element = cells[i][j].statics.begin(); element != end; element++) {
					obj = (*element);
					//if ((obj->pos().x - ViewSize.w/2 - 128 <= ViewPos.x) && (obj->pos().x + ViewSize.w/2 + 128 >= ViewPos.x)
					//&& (obj->pos().y - ViewSize.h/2 - 128 <= ViewPos.y) && (obj->pos().y + ViewSize.h/2 + 128 >= ViewPos.y))
					{
						if (!obj->draw()) {
							//std::cout << "draw static " << obj->pos().x << ", " << obj->pos().y << "\n";
							render.draw(obj->sprite, obj->pos(), obj->size(), obj->angle());
						}
					}
				}

			}
		}
	}

	if (!dynamics.empty()) {
		std::list<IObjectDynamic*>::iterator element, end;
		IObjectDynamic* dyn;

		end = dynamics.end();
		for (element = dynamics.begin (); element != end; element++) {
			dyn = (*element);
			if ((dyn->pos().x - ViewSize.w / 2 - 128 <= ViewPos.x)
					&& (dyn->pos().x + ViewSize.w / 2 + 128 >= ViewPos.x)
					&& (dyn->pos().y - ViewSize.h / 2 - 128 <= ViewPos.y)
					&& (dyn->pos().y + ViewSize.h/2 + 128 >= ViewPos.y))
			{
				if (!dyn->draw()) {
					render.draw(dyn->sprite, dyn->pos(), dyn->size(), dyn->angle());
				}
			}
		}

	}
}

void CMap::DrawParticles()
{
	CRenderManager& render = CRenderManager::GetInstance();
	std::list<IObject2D*>::iterator element;

	CPoint ViewPos = render.ViewPort();
	CBox ViewSize = render.ViewSize();

	if (!particles.empty()) {
		//glBindTexture(GL_TEXTURE_2D, decal_spr.texID);

		float cos1;
		float sin1;

		glTranslatef(-ViewPos.x-64,-ViewPos.y,0.0f);
		glBegin(GL_QUADS);

		for (element = particles.begin(); element != particles.end(); element++) {
			if (((*element)->pos().x - ViewSize.w / 2 - 64 <= ViewPos.x)
					&& ((*element)->pos().x + ViewSize.w / 2 + 64 >= ViewPos.x)
					&& ((*element)->pos().y - ViewSize.h / 2 - 64 <= ViewPos.y)
					&& ((*element)->pos().y + ViewSize.h / 2 + 64 >= ViewPos.y))
			{
				glColor4f(1.0f, 1.0f, 1.0f, (*element)->alpha());
				cos1 = 8 * Cos((*element)->angle());
				sin1 = 8 * Sin((*element)->angle());

					glTexCoord2f(1.0f, 0.0f); glVertex2f((*element)->pos().x + cos1 + sin1, (*element)->pos().y + sin1 - cos1);
					glTexCoord2f(1.0f, 1.0f); glVertex2f((*element)->pos().x + cos1 - sin1, (*element)->pos().y + sin1 + cos1);
					glTexCoord2f(0.0f, 1.0f); glVertex2f((*element)->pos().x - cos1 - sin1, (*element)->pos().y - sin1 + cos1);
					glTexCoord2f(0.0f, 0.0f); glVertex2f((*element)->pos().x - cos1 + sin1, (*element)->pos().y - sin1 - cos1);
			}
		}
		glEnd();
		glTranslatef(ViewPos.x + 64, ViewPos.y, 0.0f);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	}
}

void CMap::DrawGround()
{
	CRenderManager& render = CRenderManager::GetInstance();
	CPoint ViewPos = render.ViewPort();
	CBox ViewSize = render.ViewSize();

	float x1, y1, x2, y2;
	float _x1, _y1, _x2, _y2;
	glTranslatef(-ViewPos.x, -ViewPos.y, 0.0f);

	glBindTexture(GL_TEXTURE_2D, grounds[0].texID);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);					glVertex2f(-32, -32);
		glTexCoord2f((float)(map_w+64)/256, 0.0f);			glVertex2f(map_w+32, -32);
		glTexCoord2f((float)(map_w+64)/256, (float)(map_h+64)/256);	glVertex2f(map_w+32,map_h+32);
		glTexCoord2f(0.0f, (float)(map_h+64)/256);			glVertex2f(-32,map_h+32);
	glEnd();

	glTranslatef(0.0f,0.0f,0.0f);
	for (int mat = 1; mat < 16; mat++) {
		glBindTexture(GL_TEXTURE_2D, grounds[mat].texID);

		for (int i = 1; i < map_w / 64 + 1; i++) {
			for (int j = 1; j < map_h/64+1; j++) {
				if ((i*64 - ViewSize.w/2 - 128 <= ViewPos.x) && (i*64 + ViewSize.w/2 + 128 >= ViewPos.x)
				&& (j*64 - ViewSize.h/2 - 128 <= ViewPos.y) && (j*64 + ViewSize.h/2 + 128 >= ViewPos.y))
				{
					//текстурные координаты
					x1 = (float)(i%4)/4;
					x2 = (float)((i)%4)/4+0.25;
					y1 = (float)(j%4)/4;
					y2 = (float)((j)%4)/4+0.25;

					//координаты углов, для уменьшения математики
					_x1 = i*64-32;
					_y1 = j*64-32;
					_x2 = i*64+32;
					_y2 = j*64+32;

					glBegin(GL_QUADS);
						if (landscape[i][j] == mat) {
							//серединка
							glColor4f(1.0f,1.0f,1.0f,1.0f);
							glTexCoord2f(x1, y1); glVertex2f(_x1, _y1);
							glTexCoord2f(x2, y1); glVertex2f(_x2, _y1);
							glTexCoord2f(x2, y2); glVertex2f(_x2, _y2);
							glTexCoord2f(x1, y2); glVertex2f(_x1, _y2);

							//нижний левый угол
							if (landscape[i][j-1] != mat && landscape[i-1][j] != mat) {
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1-0.125, 	y1);		glVertex2f(_x1-32, _y1);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1-0.125, 	y1-0.125);	glVertex2f(_x1-32, _y1-32);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1, 	y1-0.125);	glVertex2f(_x1, _y1-32);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x1, 	y1);		glVertex2f(_x1, _y1);
							}

							//левый бок
							if (landscape[i-1][j] != mat) {
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1-0.125,	y1);	glVertex2f(_x1-32, _y1);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x1, 	y1);	glVertex2f(_x1, _y1);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x1, 	y2);	glVertex2f(_x1, _y2);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1-0.125,	y2);	glVertex2f(_x1-32, _y2);
							}

							//левый верхний угол
							if (landscape[i][j+1] != mat && landscape[i-1][j] != mat) {
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1-0.125,	y2);		glVertex2f(_x1-32, _y2);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x1, 	y2);		glVertex2f(_x1, _y2);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1,	y2+0.125f);	glVertex2f(_x1, _y2+32);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1-0.125,	y2+0.125f);	glVertex2f(_x1-32, _y2+32);
							}

							//правый нижний угол
							if (landscape[i][j-1] != mat && landscape[i+1][j] != mat) {
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2+0.125f,	y1);		glVertex2f(_x2+32, _y1);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x2,	y1);		glVertex2f(_x2, _y1);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2,	y1-0.125f);	glVertex2f(_x2, _y1-32);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2+0.125f,	y1-0.125f);	glVertex2f(_x2+32, _y1-32);
							}

							//правый бок
							if (landscape[i+1][j] != mat) {
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2+0.125f, y2);		glVertex2f(_x2+32, _y2);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x2, 	y2);		glVertex2f(_x2, _y2);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x2, 	y1);		glVertex2f(_x2, _y1);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2+0.125f, y1);		glVertex2f(_x2+32, _y1);
							}

							//верхний правый угол
							if (landscape[i][j+1] != mat && landscape[i+1][j] != mat) {
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2+0.125f, y2);	glVertex2f(_x2+32, _y2);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x2, y2);	glVertex2f(_x2, _y2);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2, y2+0.125);	glVertex2f(_x2, _y2+32);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2+0.125f, y2+0.125);	glVertex2f(_x2+32, _y2+32);
							}

							//верхушка
							if (landscape[i][j+1] != mat) {
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x2, y2);	glVertex2f(_x2, _y2);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x1, y2);	glVertex2f(_x1, _y2);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1, y2+0.125f);	glVertex2f(_x1, _y2+32);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2, y2+0.125f);	glVertex2f(_x2, _y2+32);
							}

							//подвал
							if (landscape[i][j-1] != mat) {
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x2, y1);	glVertex2f(_x2, _y1);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x1, y1);	glVertex2f(_x1, _y1);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1, y1-0.125f);	glVertex2f(_x1, _y1-32);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2, y1-0.125f);	glVertex2f(_x2, _y1-32);
							}

							glColor4f(1.0f,1.0f,1.0f,1.0f);
						}
					glEnd();
				}
			}
		}
	}

	glTranslatef(ViewPos.x + 64, ViewPos.y, 0.0f);
}

CMap::~CMap()
{
	uint32_t i, j;

	delete [] grounds;

	{
		std::list<IObjectStatic*>::iterator element, end;

		for (i = 0; i < cells_x; i++) {
			for (j = 0; j < cells_y; j++) {
				if (!cells[i][j].statics.empty()) {
					end = cells[i][j].statics.end();
					for (element = cells[i][j].statics.begin(); element != end; element++) {
						delete *element;
					}
				}
			}
		}
	}

	if (!dynamics.empty()) {
		std::list<IObjectDynamic*>::iterator element, end;

		end = dynamics.end();
		for (element = dynamics.begin (); element != end; element++) {
			delete *element;
		}

	}
}
