#pragma once

#include "graphics.h"
#include <SDL/SDL.h>

class CRenderManager
{
private:
	SDL_Surface *surface;
	const SDL_VideoInfo *videoInfo;
	int videoFlags;

	float day_intensity[24] =
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.00002f,					//ночь
		0.1567f, 0.3505f, 0.46136f, 0.52626f, 0.56592f,				//утро
		0.59034f, 0.6046f, 0.6112f, 0.61124f, 0.60468f, 0.59048f, 0.56614f,	//день
		0.52662f, 0.46198f, 0.35158f, 0.1585f,					//вечер
		0.00002f, 0.0f, 0.0f							//снова ночь
	};

	struct RenderJob {
		int tex_id;
		CPoint pos;
		float x1, x2, y1, y2;
		float alpha;
		float z;

		float angle;

		float tex_x1, tex_x2, tex_y1, tex_y2;

		int blend;
	};

	struct LightJob {
		int tex_id;
		CPoint pos;
		float angle;
		float x1, x2, y1, y2;
		TColor color;
	};
	typedef RenderJob* job;
	typedef LightJob* ljob;
	job* queue;
	ljob* light_queue;
	bool _lights;
	int queue_len;
	int lqueue_len;

	int queue_alloc;
	int lqueue_alloc;

	int minutes;
	float global_alpha;

	void swap_job(job &j1, job &j2)
	{
		job tmp = j1;
		j1 = j2;
		j2 = tmp;
	}

	void sort_job(int first, int last);

	bool sdl_init(int w, int h);

	struct ShadowBuffer {
		float w;
		float h;

		GLuint buffer;
		GLuint texid;
		GLuint rboId;
	} sbuff;

	CBox lvl_size;
	CBox view_size;
	CPoint view_pos;

	bool full_screen;
public:
	int wnd_height, wnd_width;
	static CRenderManager& GetInstance();

	CRenderManager(float w = 1024, float h = 600, bool full = false);

	void resize(float w, float h);

	void toggle_full_screen();

	void InitShadowBuffer(int w, int h);

	void draw(Sprite *tex, CVector pos, CBox size, float angle, float alpha = 1, int blend = 0);
	void draw_light(Sprite *tex, CVector pos, CBox size, float angle, TColor c = color(1.0f,1.0f,1.0f,1.0f));

	void set_lights(bool en) { _lights = en; }

	void render();
	void clear_jobs();

	void LevelResize(float w, float h);
	void ViewSize(float w, float h);
	CBox ViewSize();
	void ViewPort(CPoint pos);
	void ViewPort(CVector pos);
	CPoint ViewPort();

	float w2m_x(float x);
	float w2m_y(float y);

	float m2w_x(float x);
	float m2w_y(float y);

	void set_time(int time);
	void set_alpha(float a) { global_alpha = a; }

	void mrproper();

	~CRenderManager();
};
