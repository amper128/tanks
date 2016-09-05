#include <game/CGame.h>

//TFont* font1;

CGame::CGame()
{
	render	= &CRenderManager::GetInstance();
	input	= &CInputManager::GetInstance();

//	config	= CConfigManager::GetInstance();
//	resman	= CResourceManager::GetInstance();
//	memman	= CMemoryManager::GetInstance();

	fabric = &CFabric::GetFabric();

	game_time = 19*60;

	paused = false;
}

void CGame::start()
{
//	render->resize(1024,600);

	times = MilliSecs();
	srand(MilliSecs());

	fps = 0;
	fps_timer = 0;

	period = 10;

	font1 = new TFont();
	font1->LoadFont(string("font1"));

	pause_label = new GUI_Label(render->m2w_x(render->ViewSize().w / 2),
				    render->m2w_y(render->ViewSize().h / 2));
	pause_label->setfont(font1);
	pause_label->settext("[ pause... ]");
	pause_label->setcolor(color(0, 255, 0, 1));

	level = new CMap();
	level->loadmap("level13");

	fabric->setmap(level);

	render->LevelResize(level->map_w, level->map_h);

	tank = new TTank;
	level->dynamics.push_back(tank);

	font2 = new TFont();
	font2->LoadFont(string("font2"));

	render->set_time(20*60);
}

void CGame::stop()
{
	//delete render;
	//render->mrproper();
}

bool CGame::gameloop()
{
	SDL_Event event;
	unsigned int oldtime = times;

	while (SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_KEYDOWN:
			input->press_key(event.key.keysym.sym,0,0);
			break;

		case SDL_KEYUP:
			input->up_key(event.key.keysym.sym,0,0);
			break;

		case SDL_MOUSEMOTION:
			float x;
			x = event.motion.x;
			float y;
			y = event.motion.y;
			x = render->w2m_x(x);
			y = render->w2m_y(y);
			input->mouse_move(x,y);
			break;

		case SDL_VIDEORESIZE:
			//render->resize(event.resize.w, event.resize.h);
			break;

		case SDL_QUIT:
			return false;
			break;
		}
	}

	if (input->keyhit(27)) {
		return false;
	}

	do {
		elapsed=MilliSecs()-times;
	} while (!elapsed);

	ticks = elapsed/period;

	for (int k = 1; k < ticks; k++) {
		times=times+period;
		stepgame();
	}

	if (fps_timer == 0) {
		fps_timer = 100;
		fps = 100000.0f/(MilliSecs() - fps_st);
		fps_st = MilliSecs();
	}

	fps_timer--;
	DrawGame();

	delta = MilliSecs() - oldtime;

//	printf("delta: %i\noldtime: %i\nelapsed: %i\n",delta,oldtime,elapsed);

	return true;
}

void CGame::stepgame()
{
	/*if (input->keyhit(VK_F4)) {
		if (_full) {
			_full = false;
			SDL_WM_ToggleFullScreen(surface);
		} else {
			_full = true;
			SDL_WM_ToggleFullScreen(surface);
		}
	}*/

	if (input->keyhit(VK_N)) {
		lights_enable = !lights_enable;
		render->set_lights(lights_enable);
	}

	if (input->keyhit(VK_P)) {
		if (paused) {
			paused = false;
		} else {
			paused = true;
		}
	}

	if (!paused) {
		if (input->keydown(VK_W)) tank->setmov(moving_forward);
		else if (input->keydown(VK_S)) tank->setmov(moving_backward);
		else tank->setmov(moving_none);

		if (input->keydown(VK_D)) tank->setsteer(steering_right);
		else if (input->keydown(VK_A)) tank->setsteer(steering_left);
		else tank->setsteer(steering_none);

		if (input->keydown(VK_F)) tank->kill();

		if (input->keydown(VK_LEFT)) tank->setwpnrot(rotation_left);
		else if (input->keydown(VK_RIGHT)) tank->setwpnrot(rotation_right);
		else tank->setwpnrot(rotation_none);

		if (input->keydown(VK_SPACE)) tank->shot();

		if (input->keyhit(VK_L)) tank->set_light(!tank->light());

		if (game_time >= 1440) game_time -=1440;
		if (game_time < 0) game_time += 1440;

		minute_timer--;
		if (minute_timer <= 0) {
			game_time ++;
			render->set_time(game_time);
			minute_timer = 30;
		}

		level->step_objects();
	}

	render->ViewPort(tank->pos());

	input->reset_keystate();
}

void CGame::DrawGame()
{
	int hours, minutes;

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	level->DrawGround();
	level->DrawParticles();
	level->DrawObjects();

	//render->set_time(6000);
	render->render();

	if (paused) {
		font2->DrawStringCenter("[ пауза... ]",
					render->m2w_x(render->ViewSize().w/2),
					render->m2w_y(render->ViewSize().h/2),
					color(0, 255, 0, 1.0f));
		//pause_label->draw();
	}

	hours = game_time / 60;
	minutes = game_time - (hours * 60);

	font2->DrawString(string("fps: ") + ftostr(fps),16, 32,color(255,255,255,0.5));
	font2->DrawString(string("time: ") + string(inttostr(hours)) + ":" + string(inttostr(minutes)), 300, 32,color(255,255,255,0.5));
	glFlush();
	SDL_GL_SwapBuffers();
}

CGame::~CGame()
{
	delete font1;
	delete font2;
	//delete pause_label;
	delete level;
}
