#pragma once

#include <graphics/render_manager.h>
#include <system/input_manager.h>
#include <system/config_manager.h>
#include <system/resource_manager.h>
#include <system/memory_manager.h>
#include <game/SCMap.h>
#include <game/IObjectBase.h>
#include <game/SCFabric.h>
#include <gui/label.h>

#include <game/GCVehicleMiddleTank.h>

class CGame
{
private:
	CRenderManager*		render;
	CInputManager*		input;
	CConfigManager*		config;
	CResourceManager*	resman;
	CMemoryManager*		memman;
	CFabric*		fabric;

	CMap*			level;

	float fps;
	int fps_timer;
	int fps_st;

	long int times;
	int elapsed,ticks,delta;
	int period;

	bool paused;

	short game_time;
	short minute_timer;
	bool lights_enable;

	bool _full;
//FIXME
	TTank* tank;
	TFont* font1;
	TFont* font2;

	GUI_Label* pause_label;
public:
	CGame();

	void start();
	void stop();

	bool gameloop();
	void stepgame();
	void DrawGame();

	~CGame();
};
