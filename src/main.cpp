//
bool keystate[256];

#include "main.h"
#include "graphics/window.cpp"
#include "game/landscape.cpp"
SDL_Surface *surface;

bool played = false;
long int times = 0l;
int elapsed,ticks,delta;
const int period = 10;

GLfloat angle;

TTank *tank;

bool _full;
bool light_enable = false;

int minutes = 18*60;
int minute_timer = 20;

int videoFlags;
SDL_Event event;

void Quit( int returnCode )
{
	SDL_Quit( );
	printf("exiting...\n");
	exit( returnCode );
}

void stepgame()
{
	if (keys_down[VK_W]) tank->setmov(1);
	else if (keys_down[VK_S]) tank->setmov(2);
	else tank->setmov(0);

	if (keys_down[VK_D]) tank->setsteer(1);
	else if (keys_down[VK_A]) tank->setsteer(2);
	else tank->setsteer(0);

	if (keys_down[VK_F]) tank->kill();

	if (keys_down[VK_LEFT]) tank->setwpnrot(1);
	else if (keys_down[VK_RIGHT]) tank->setwpnrot(2);
	else tank->setwpnrot(0);

	if (keys_down[VK_SPACE]) tank->shot();

	if (keys_pressed[VK_F4])
	{
		if (_full)
		{
			_full = false;
			//glutReshapeWindow(1280,720);
		}
		else
		{
			_full = true;
			//glutFullScreen();
		}
	}

	if (keys_pressed[VK_N])
	{
		light_enable = !light_enable;
		render.set_lights(light_enable);
	}

	if (keys_pressed[VK_P]) minutes++;
	if (keys_pressed[VK_O]) minutes--;

	if (keys_pressed[VK_L]) tank->set_light(!tank->light());

	if (minutes >= 1440) minutes -=1440;
	if (minutes < 0) minutes += 1440;

	//float an;
	//an = DegreesBetweenPoints(tank->getpos(),mouse_pos);

	//printf("mouse: %f %f\n",mouse_pos.x,mouse_pos.y);
	//printf("tank: %f %f\n",tank->pos().x,tank->pos().y);
	//tank->setwpnangle(an);
//	tank->step();
	minute_timer--;
	if (minute_timer <= 0)
	{
		minutes ++;
		minute_timer = 30;
	}
	MAP.step_objects();

	ViewPort(tank->pos());
	//reset_keystate();
}

void drawgame()
{
	//printf("clear!\n");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
	//printf("bbbbbbbb!\n");
	glLoadIdentity();						// Reset The View

	DrawLand();
	if (keys_down[VK_G])
	{
		DrawGrid();
	}
	DrawDecals();
	DrawTanks();
	DrawObjects();

	render.set_time(minutes);
	render.render();

	SDL_GL_SwapBuffers( );
//	glutSwapBuffers();
	//printf("wwwwww!\n");
}

bool gameloop()
{
	while ( SDL_PollEvent( &event ) )
	{
		switch( event.type )
		{
			case SDL_KEYDOWN:
				//printf("%i key was pressed! Input was \"%s\"\n",event.key.keysym.sym,event.key.keysym.scancode);
				press_key( event.key.keysym.sym ,0,0);
				break;
			case SDL_KEYUP:
				up_key( event.key.keysym.sym ,0,0);
				break;
			case SDL_VIDEORESIZE:
				surface = SDL_SetVideoMode( event.resize.w,event.resize.h,24, videoFlags );
				if ( !surface )
				{
					printf( "Could not get a surface after resize: %s\n", SDL_GetError( ) );
					Quit( 1 );
				}
				ReSizeGLScene(event.resize.w, event.resize.h);
				break;
			case SDL_QUIT:
				return false;
				break;
		}
	}
	if (keys_pressed[VK_ESCAPE])
	{
		return false;
		//выход!
	}

	int oldtime = times;
	do
	{
		elapsed=MilliSecs()-times;
	} while (!elapsed);

	ticks=elapsed/period;

	for (int k=1; k<ticks; k++)
	{
		times=times+period;
		stepgame();
	}

	drawgame();
	delta = MilliSecs() - oldtime;
	Delay(delta/2);

	reset_keystate();
	return true;
}

#ifdef _WIN32
//#define WIN32 
//INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPCSTR, INT)
int SDL_main(int argc, char **argv)
#else
int main(int argc, char **argv)
#endif
{
//	assertExtensionsSupported ( "ARB_pixel_buffer_object" );
	printf("Starting...\n");

	const SDL_VideoInfo *videoInfo;
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "Video initialization failed: %s\n", SDL_GetError( ) );
		Quit( 1 );
	}

	videoInfo = SDL_GetVideoInfo( );

	if ( !videoInfo )
	{
		printf( "Video query failed: %s\n", SDL_GetError( ) );
		Quit( 1 );
	}

	videoFlags  = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_RESIZABLE;

	if ( videoInfo->hw_available )
	{
		videoFlags |= SDL_HWSURFACE;
	}
	else
	{
		videoFlags |= SDL_SWSURFACE;
	}

	if ( videoInfo->blit_hw )
	{
		videoFlags |= SDL_HWACCEL;
	}

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	//if ( initGL( ) == FALSE )
	{
	//	printf("Could not initialize OpenGL.\n" );
	//	Quit( 1 );
	}

	//resizeWindow( 800, 600 );

	played = true;
	settings.gm_fullscreen = false;
	printf("init OpenGL...\n");
	times = MilliSecs();

	surface = SDL_SetVideoMode( 800, 600, 32,videoFlags );

	if ( !surface )
	{
		printf( "Video mode set failed: %s\n", SDL_GetError( ) );
		Quit( 1 );
	}

	if ( ( SDL_EnableKeyRepeat( 100, SDL_DEFAULT_REPEAT_INTERVAL ) ) )
	{
		fprintf( stderr, "Setting keyboard repeat failed: %s\n", SDL_GetError( ) );
		Quit( 1 );
	}
	initwnd(0, NULL);

	printf("init random seed...\n");
	srand(MilliSecs());

	printf("Setting up drawing modes...\n");
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable (GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glHint (GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);

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

	decal_spr = LoadSpr("gamedata/textures/decals/trac.tga");
	tree_spr = LoadSpr("gamedata/textures/objects/tree.tga");

	grid = LoadSpr("gamedata/textures/editor/grid.tga");
	std::string str;
	str = "lights/round.tga";
	light_omni = TexManager.load(str,point(0,0));

	str = "lights/spot.tga";
	light_spot = TexManager.load(str,point(0,256));

	MAP.loadmap("level08");

	tank = new TTank;
	MAP.dynamics.push_back(tank);
	printf("tank created!\n");

	//glutMainLoop();
	while (gameloop());

	Quit(0);
}
