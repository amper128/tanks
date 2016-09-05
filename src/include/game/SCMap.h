#pragma once

#include <list>
#include <system/vectors.h>
#include <graphics/render_manager.h>
#include <game/object_defs.h>
#include <game/IObject2D.h>
#include <game/IObjectStatic.h>
#include <game/IObjectDynamic.h>

struct CCell
{
	std::list<IObjectStatic*> statics;
};

class CMap
{
private:
	Texture *grounds;
public:
	CMap();

	uint8_t ** landscape;
	void loadmap(std::string name);

	CCell ** cells;
	uint32_t cells_x;
	uint32_t cells_y;

	std::list<IObject2D*> particles;
	std::list<IObjectStatic*> statics;
	std::list<IObjectDynamic*> dynamics;

	void DrawGround();
	void DrawObjects();
	void DrawParticles();

	void step_objects();
	void add_object(float x, float y, object_types type);

	void add_static(float x, float y, std::string type);
	void add_dynamic(float x, float y, std::string type);

	float map_w;
	float map_h;

	~CMap();
};
