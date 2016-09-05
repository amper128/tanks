#include <graphics/render_manager.h>

CRenderManager::CRenderManager(float w, float h, bool full)
{
	if (!sdl_init(w,h)) exit(-1);

	glewInit();

	glViewport(0, 0, int(w), int(h));

	view_size.w = w/h*1024;
	view_size.h = 1024;

	glMatrixMode(GL_PROJECTION);
	glOrtho(-view_size.w/2, view_size.w/2, -view_size.h/2, view_size.h/2, -128, 256);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable (GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glHint (GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	queue_len = 0;
	queue = new job[queue_len];

	lqueue_len = 0;
	light_queue = new ljob[lqueue_len];

	minutes = 0;
	_lights = false;

	queue_alloc = 0;
	lqueue_alloc = 0;

	wnd_height = h;
	wnd_width = w;

	global_alpha = 1.0f;

	InitShadowBuffer(w, h);
}

bool CRenderManager::sdl_init(int w, int h)
{
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "Video initialization failed: %s\n", SDL_GetError( ) );
		exit( 1 );
	}

	videoInfo = SDL_GetVideoInfo( );

	if ( !videoInfo ) {
		printf( "Video query failed: %s\n", SDL_GetError( ) );
		exit( 1 );
	}

	videoFlags  = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_SRCALPHA | SDL_HWSURFACE | SDL_HWACCEL;

	if ( videoInfo->hw_available ) {
		videoFlags |= SDL_HWSURFACE;
		printf("Hardware rendering...\n");
	} else {
		videoFlags |= SDL_SWSURFACE;
		printf("Software rendering...\n");
	}

	if ( videoInfo->blit_hw ) {
		videoFlags |= SDL_HWACCEL;
		printf("Hardware acceleration enabled...\n");
	}

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	surface = SDL_SetVideoMode( w, h, 32,videoFlags );

	if ( !surface ) {
		printf( "Video mode set failed: %s\n", SDL_GetError( ) );
		exit( 1 );
	}

	if ( ( SDL_EnableKeyRepeat( 100, SDL_DEFAULT_REPEAT_INTERVAL ) ) ) {
		fprintf( stderr, "Setting keyboard repeat failed: %s\n", SDL_GetError( ) );
		exit( 1 );
	}

	SDL_WM_SetCaption("Tanks v0.01 pre-alpha", "ex2");

	return true;
}

CRenderManager& CRenderManager::GetInstance()
{
	static CRenderManager _instance;
	return _instance;
}

void CRenderManager::resize(float w, float h)
{
	if (h < 480) h = 480;
	if (w < 640) w = 640;

	glViewport(0, 0, int(w), int(h));

	wnd_height = h;
	wnd_width = w;

	view_size.w = w/h * 1024;
	view_size.h = 1024;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-view_size.w/2, view_size.w/2, -view_size.h/2, view_size.h/2, -128, 256);
	glMatrixMode(GL_MODELVIEW);

	surface = SDL_SetVideoMode(int(wnd_width), int(wnd_height), 32, videoFlags );
	if (!surface) {
		printf( "Could not get a surface after resize: %s\n", SDL_GetError( ) );
		exit( 1 );
	}

	InitShadowBuffer(w, h);
}

void CRenderManager::ViewSize(float w, float h)
{
	view_size.w = w;
	view_size.h = h;
}

CBox CRenderManager::ViewSize()
{
	return view_size;
}

void CRenderManager::ViewPort(CPoint pos)
{
	view_pos = pos;
	if (lvl_size.w + 64 < view_size.w) {
		view_pos.x = lvl_size.w / 2;
	} else {
		view_pos.x = max(view_pos.x, view_size.w / 2 - 32);
		view_pos.x = min(view_pos.x, lvl_size.w - view_size.w / 2 + 32);
	}

	if (lvl_size.h + 64 < view_size.h) {
		view_pos.y = lvl_size.h / 2;
	} else {
		view_pos.y = max(view_pos.y, view_size.h / 2 - 32);
		view_pos.y = min(view_pos.y, lvl_size.h - view_size.h / 2 + 32);
	}
}

void CRenderManager::ViewPort(CVector pos)
{
	view_pos.x = pos.x;
	view_pos.y = pos.y;

	if (lvl_size.w + 64 < view_size.w) {
		view_pos.x = lvl_size.w / 2;
	} else {
		view_pos.x = max(view_pos.x, view_size.w / 2 - 32);
		view_pos.x = min(view_pos.x, lvl_size.w - view_size.w / 2 + 32);
	}

	if (lvl_size.h + 64 < view_size.h) {
		view_pos.y = lvl_size.h / 2;
	} else {
		view_pos.y = max(view_pos.y, view_size.h / 2 - 32);
		view_pos.y = min(view_pos.y, lvl_size.h - view_size.h / 2 + 32);
	}
}

CPoint CRenderManager::ViewPort()
{
	return view_pos;
}

void CRenderManager::LevelResize(float w, float h)
{
	lvl_size.h = h;
	lvl_size.w = w;
}

float CRenderManager::w2m_x(float x)
{
	return x/wnd_width*view_size.w;
}

float CRenderManager::w2m_y(float y)
{
	return y/wnd_height*view_size.h;
}

float CRenderManager::m2w_x(float x)
{
	return x/view_size.w*wnd_width;
}

float CRenderManager::m2w_y(float y)
{
	return y/view_size.h*wnd_height;
}

void CRenderManager::InitShadowBuffer(int w, int h)
{
	if (sbuff.texid != 0)
		glDeleteTextures(1, &(sbuff.texid));
	if (sbuff.buffer != 0)
		glDeleteFramebuffersEXT(1, &sbuff.buffer);
	if (sbuff.rboId != 0)
		glDeleteRenderbuffersEXT(1, &sbuff.rboId);

	int w2 = 512, h2 = 512;
	if (w > 512) w2 = 1024;
	if (w > 1024) w2 = 2048;
	if (w > 2048) w2 = 4096;

	if (h > 512) h2 = 1024;
	if (h > 1024) h2 = 2048;
	if (h > 2048) h2 = 4096;

	sbuff.h = h2;
	sbuff.w = w2;

	GLenum status;
	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch(status)
	{
	case GL_FRAMEBUFFER_COMPLETE_EXT:
		printf("1. GL_FRAMEBUFFER_EXT SUCCESS\n");
		break;
	default:
		printf("1. GL_FRAMEBUFFER_EXT FAIL\n");
		break;
	}

	printf("glGenFramebuffersEXT...\n");
	glGenFramebuffersEXT(1,&sbuff.buffer);
	if (sbuff.buffer == 0)
	{
		printf("glGenFramebuffersEXT FAIL. Exiting....\n");
		exit(-1);
	}

	printf("glGenTextures...\n");
	glGenTextures(1, &sbuff.texid);
	if (sbuff.texid == 0)
	{
		printf("glGenTextures FAIL. Exiting....\n");
		exit(-1);
	}

	printf("glBindTexture...\n");
	glBindTexture(GL_TEXTURE_2D, sbuff.texid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	printf("glTexImage2D...\n");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w2, h2, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);

	printf("glBindFramebufferEXT...\n");
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, sbuff.buffer);

	printf("glFramebufferTexture2DEXT...\n");
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, sbuff.texid, 0);

	printf("glGenRenderbuffersEXT...\n");
	glGenRenderbuffersEXT(1, &sbuff.rboId);
	if (sbuff.rboId == 0) {
		printf("glGenRenderbuffersEXT FAIL. Exiting....\n");
		exit(-1);
	}

	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, sbuff.rboId);

	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch(status) {
	case GL_FRAMEBUFFER_COMPLETE_EXT:
		printf("2. GL_FRAMEBUFFER_EXT SUCCESS\n");
		break;
	default:
		printf("2. GL_FRAMEBUFFER_EXT FAIL\n");
		break;
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

}

void CRenderManager::draw(Sprite *tex, CVector pos, CBox size, float angle, float alpha, int blend)
{
	if (queue_len + 1 > queue_alloc) {
		job* tmp;
		int i;
		int new_len = queue_len * 2 + 1;

		tmp = new job[new_len];

		for (i = 0; i < queue_len; i++)
			tmp[i] = queue[i];
		for (i = queue_len; i < new_len; i++)
			tmp[i] = new RenderJob;
		delete[] queue;

		queue = tmp;
		queue_alloc = new_len;
	}

	queue[queue_len]->z = pos.z;
	queue[queue_len]->alpha = alpha*global_alpha;
	queue[queue_len]->angle = angle;
	queue[queue_len]->tex_id = tex->texID;
	queue[queue_len]->pos.x = pos.x;
	queue[queue_len]->pos.y = pos.y;
	queue[queue_len]->pos.z = pos.z;

	queue[queue_len]->x1 = -size.w/2+tex->orig_x;
	queue[queue_len]->x2 =  size.w/2+tex->orig_x;
	queue[queue_len]->y1 = -size.h/2+tex->orig_y;
	queue[queue_len]->y2 =  size.h/2+tex->orig_y;

	queue[queue_len]->tex_x1 = float((tex->frame) % tex->frames_x)/tex->frames_x;
	queue[queue_len]->tex_x2 = queue[queue_len]->tex_x1 + 1.0f/tex->frames_x;
	queue[queue_len]->tex_y1 = float(tex->frames_y - (tex->frame/tex->frames_y+1))/tex->frames_y;
	queue[queue_len]->tex_y2 = queue[queue_len]->tex_y1 + 1.0f/tex->frames_y;
	++queue_len;
}

void CRenderManager::draw_light(Sprite *tex, CVector pos, CBox size, float angle, TColor col)
{
	if (!_lights) {
		/* no lights */
		return;
	}

	if (lqueue_len + 1 > lqueue_alloc) {
		ljob* tmp;
		int i;
		int new_len = lqueue_len*2+1;

		tmp = new ljob[new_len];

		for (i = 0; i < lqueue_len; i++) {
			tmp[i] = light_queue[i];
		}

		for (i = lqueue_len; i < new_len; i++) {
			tmp[i] = new LightJob;
		}

		delete [] light_queue;

		light_queue = tmp;
		lqueue_alloc = new_len;
	}

	light_queue[lqueue_len]->color		= col;
//	light_queue[lqueue_len]->color.a	/= 0.5;
	light_queue[lqueue_len]->tex_id		= tex->texID;
	light_queue[lqueue_len]->pos.x		= pos.x;
	light_queue[lqueue_len]->pos.y		= pos.y;
	light_queue[lqueue_len]->pos.z		= pos.z;
	light_queue[lqueue_len]->angle		= angle;

	light_queue[lqueue_len]->x1 = -size.w+tex->orig_x;
	light_queue[lqueue_len]->x2 =  size.w+tex->orig_x;
	light_queue[lqueue_len]->y1 = -size.h+tex->orig_y;
	light_queue[lqueue_len]->y2 =  size.h+tex->orig_y;
	++lqueue_len;
}

void CRenderManager::sort_job(int first, int last)
{
	int i = first, j = last, x = queue[(first + last) / 2]->z;

	do {
		while (queue[i]->z < x) i++;
		while (queue[j]->z > x) j--;
		if (i <= j) {
			if (i < j) {
				swap_job(queue[i], queue[j]);
			}
			i++;
			j--;
		}
	} while (i <= j);

	if (i < last)
		sort_job(i, last);
	if (first < j)
		sort_job(first,j);
}

void CRenderManager::render()
{
	int old_tex_id = 0;
//	float p_x, p_y, p_z;

	//сортировка
	sort_job(0,queue_len-1);

	glLoadIdentity();
	glTranslatef(-view_pos.x,-view_pos.y,0.0f);
	for (int i=0; i< queue_len; i++) {
		glColor4f(1.0f, 1.0f, 1.0f, queue[i]->alpha);
		if (queue[i]->tex_id != old_tex_id) {
			glBindTexture(GL_TEXTURE_2D, queue[i]->tex_id);
			old_tex_id = queue[i]->tex_id;
		}
		glTranslatef(queue[i]->pos.x,queue[i]->pos.y,queue[i]->z);
		glRotatef(queue[i]->angle,0.0f,0.0f,1.0f);

		glBegin(GL_QUADS);
			glTexCoord2f(queue[i]->tex_x1, queue[i]->tex_y1); glVertex2f(queue[i]->x1, queue[i]->y1);
			glTexCoord2f(queue[i]->tex_x2, queue[i]->tex_y1); glVertex2f(queue[i]->x2, queue[i]->y1);
			glTexCoord2f(queue[i]->tex_x2, queue[i]->tex_y2); glVertex2f(queue[i]->x2, queue[i]->y2);
			glTexCoord2f(queue[i]->tex_x1, queue[i]->tex_y2); glVertex2f(queue[i]->x1, queue[i]->y2);
		glEnd();

		glRotatef(-queue[i]->angle,0.0f,0.0f,1.0f);
		glTranslatef(-queue[i]->pos.x,-queue[i]->pos.y,-queue[i]->z);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	glTranslatef(view_pos.x,view_pos.y,0.0f);
	glBindTexture(GL_TEXTURE_2D, 0);


	//освещение (пока тестово)
	if (_lights) {
		float lighting_r = 1.0f;
		float lighting_g = 0.949019608f;
		float lighting_b = 0.898039216f;

		int hour = minutes / 60;
		int mins = minutes - hour*60;
		float intens;
		int next_hour = hour + 1;
		float _r,_g,_b;
		float opos_x = 0, opos_y = 0;

		if (next_hour > 23) next_hour -= 24;
		intens = day_intensity[hour] + (day_intensity[next_hour] - day_intensity[hour]) / 60 * mins;
	//	printf("time: %i:%i; light: %.3f\n",hour, mins,intens);

		_r = 0.02 * (0.615-intens) + lighting_r*intens;
		_g = 0.02 * (0.615-intens) + lighting_g*intens;
		_b = 0.05 * (0.615-intens) +lighting_b*intens;

		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, sbuff.rboId);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, sbuff.buffer);
		glClearColor(_r, _g, _b, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

		glTranslatef(-view_pos.x,-view_pos.y,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		old_tex_id = 0;
		glTranslatef(0,0,128);

		for (int i=0; i< lqueue_len; i++) {
			glColor4f(light_queue[i]->color.r, light_queue[i]->color.g, light_queue[i]->color.b, light_queue[i]->color.a * (1-intens*1.5));
			if (light_queue[i]->tex_id != old_tex_id) {
				glBindTexture(GL_TEXTURE_2D, light_queue[i]->tex_id);
				old_tex_id = light_queue[i]->tex_id;
			}
			glTranslatef(light_queue[i]->pos.x - opos_x,light_queue[i]->pos.y - opos_y,0);
			opos_x = light_queue[i]->pos.x;
			opos_y = light_queue[i]->pos.y;

			glRotatef(light_queue[i]->angle,0.0f,0.0f,1.0f);
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0); glVertex2f(light_queue[i]->x1, light_queue[i]->y1);
				glTexCoord2f(1, 0); glVertex2f(light_queue[i]->x2, light_queue[i]->y1);
				glTexCoord2f(1, 1); glVertex2f(light_queue[i]->x2, light_queue[i]->y2);
				glTexCoord2f(0, 1); glVertex2f(light_queue[i]->x1, light_queue[i]->y2);
			glEnd();
			glRotatef(-light_queue[i]->angle,0.0f,0.0f,1.0f);

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		}
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

		//рендер "теневого" буфера
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		glLoadIdentity();
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
//		glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
//		glTranslatef(-view_pos.x,-view_pos.y,0.0f);
		glBindTexture(GL_TEXTURE_2D, sbuff.texid);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,			0.0f);				glVertex3f(-view_size.w/2, -512, 128);
			glTexCoord2f(float(wnd_width)/sbuff.w,	0.0f);				glVertex3f(view_size.w/2, -512, 128);
			glTexCoord2f(float(wnd_width)/sbuff.w,	float(wnd_height)/sbuff.h);	glVertex3f(view_size.w/2,  512, 128);
			glTexCoord2f(0.0f,			float(wnd_height)/sbuff.h);	glVertex3f(-view_size.w/2,  512, 128);
		glEnd();
	//	glTranslatef(view_pos.x,view_pos.y,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	clear_jobs();
//	glClearColor(0, 0, 0, 1);
}


void CRenderManager::clear_jobs()
{
	queue_len = 0;
	lqueue_len = 0;
}

void CRenderManager::set_time(int time)
{
	minutes = time;
}

void CRenderManager::mrproper()
{
	int i;

	for (i = 0; i < queue_alloc; i++) {
		delete queue[i];
	}

	for (i = 0; i < lqueue_alloc; i++) {
		delete light_queue[i];
	}

	if (sbuff.texid != 0)
		glDeleteTextures(1, &sbuff.texid);
	if (sbuff.buffer != 0)
		glDeleteFramebuffersEXT(1, &sbuff.buffer);
	if (sbuff.rboId != 0)
		glDeleteRenderbuffersEXT(1, &sbuff.rboId);

	SDL_Quit();
}

CRenderManager::~CRenderManager()
{
	mrproper();
}
