#pragma once

#include "texture.h"
#include "glext.h"

#include "../game/baseobject.h"

class RenderManager
{
	class RenderJob
	{
	public:
		int tex_id;
		Tpoint pos;
		float x1, x2, y1, y2;
		float alpha;
		float z;

		float angle;

		float tex_x1, tex_x2, tex_y1, tex_y2;

		int blend;
	};

	class LightJob : public BaseObj
	{
	public:
		int tex_id;
		Tpoint pos;
		float angle;
		float x1, x2, y1, y2;
		TColor color;
	};
	typedef RenderJob* job;
	typedef LightJob* ljob;

private:
	job* queue;
	ljob* light_queue;
	bool _lights;
	int queue_len;
	int lqueue_len;

	int minutes;
public:
	RenderManager();

	void draw(Sprite *tex, Tpoint pos, Tbox size, float angle, float z = 0, float alpha = 1, int blend = 0);
	void draw_light(Sprite *tex, Tpoint pos, Tbox size, float angle, TColor c = color(1.0f,1.0f,1.0f,1.0f));

	void set_lights(bool en) { _lights = en; };

	void render();
	void clear_jobs();

	void set_time(int time);

	~RenderManager();
} render;
