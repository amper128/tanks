#include "render_manager.h"

RenderManager::RenderManager()
{
	queue_len = 0;
	queue = new job[queue_len];

	lqueue_len = 0;
	light_queue = new ljob[lqueue_len];

	minutes = 0;
	_lights = true;
}

RenderManager::~RenderManager()
{
	for (int i=0; i< queue_len; i++)
	{
	//	delete queue[i];
	}
	delete queue;
}

void RenderManager::draw(Sprite *tex, Tpoint pos, Tbox size, float angle, float z, float alpha, int blend)
{
	job* tmp;
	job new_job;

	new_job = new RenderJob;
	new_job->z = z;
	new_job->alpha = alpha;
	new_job->angle = angle;
	new_job->tex_id = tex->texID;
	new_job->pos = pos;

	new_job->x1 = -size.w/2+tex->orig_x;
	new_job->x2 =  size.w/2+tex->orig_x;
	new_job->y1 = -size.h/2+tex->orig_y;
	new_job->y2 =  size.h/2+tex->orig_y;

	new_job->tex_x1 = float((tex->frame) % tex->frames_x)/tex->frames_x;
	new_job->tex_x2 = new_job->tex_x1 + 1.0f/tex->frames_x;
	new_job->tex_y1 = float(tex->frames_y - (tex->frame/tex->frames_y+1))/tex->frames_y;
	new_job->tex_y2 = new_job->tex_y1 + 1.0f/tex->frames_y;

//	new_job->blend = blend;

	tmp = new job[++queue_len];
	int i,j;
	j = queue_len-1;
	for (i=0; i<queue_len-1; i++)
	{
		if (queue[i]->z >= new_job->z)
		{
			{
				j = i;
				break;
			}
		}
		tmp[i] = queue[i];
	}
	tmp[j] = new_job;
	for (i=j;i<queue_len-1;i++)
	{
		tmp[i+1] = queue[i];
	}
	delete queue;
	queue = tmp;

/*	if (blend == 1)
	{
		ljob* tmp2;
		ljob new_job2;

		new_job2 = new LightJob;
		new_job2->color.a = alpha*0.5;
		new_job2->tex_id = light_round.texID;
		new_job2->pos = pos;

		new_job2->x1 = -size.w+tex->orig_x;
		new_job2->x2 =  size.w+tex->orig_x;
		new_job2->y1 = -size.h+tex->orig_y;
		new_job2->y2 =  size.h+tex->orig_y;

		//job* tmp2;
		tmp2 = new ljob[++lqueue_len];
		j = lqueue_len-1;
		for (i=0; i<lqueue_len-1; i++)
		{
			tmp2[i] = light_queue[i];
		}
		tmp2[j] = new_job2;
		delete light_queue;
		light_queue = tmp2;
	}*/
}

void RenderManager::draw_light(Sprite *tex, Tpoint pos, Tbox size, float angle, TColor col)
{
	ljob* tmp2;
	ljob new_job2;

	new_job2 = new LightJob;
	new_job2->color = col;
	new_job2->color.a /= 0.5;
	new_job2->tex_id = tex->texID;
	new_job2->pos = pos;
	new_job2->angle = angle;

	new_job2->x1 = -size.w+tex->orig_x;
	new_job2->x2 =  size.w+tex->orig_x;
	new_job2->y1 = -size.h+tex->orig_y;
	new_job2->y2 =  size.h+tex->orig_y;

	int i,j;
	//job* tmp2;
	tmp2 = new ljob[++lqueue_len];
	j = lqueue_len-1;
	for (i=0; i<j; i++)
	{
		tmp2[i] = light_queue[i];
	}
	tmp2[j] = new_job2;
	delete light_queue;
	light_queue = tmp2;
}

void RenderManager::render()
{
	int old_tex_id = 0;
	float p_x, p_y, p_z;

	glTranslatef(-ViewPos.x,-ViewPos.y,0.0f);
	for (int i=0; i< queue_len; i++)
	{
		//if ((queue[i]->x1 - viewport_w/2 - 32 <= ViewPos.x) && (queue[i]->x2 + viewport_w/2 + 32 >= ViewPos.x))
		//&&  (queue[i]->y1 - viewport_h/2 - 32 <= ViewPos.y) && (queue[i]->y2 + viewport_h/2 + 32 >= ViewPos.y))
		{
			glColor4f(1.0f, 1.0f, 1.0f, queue[i]->alpha);
			if (queue[i]->tex_id != old_tex_id)
			{
				glBindTexture(GL_TEXTURE_2D, queue[i]->tex_id);
				old_tex_id = queue[i]->tex_id;
			}
			glTranslatef(queue[i]->pos.x,queue[i]->pos.y,queue[i]->z);
			glRotatef(queue[i]->angle,0.0f,0.0f,1.0f);
			{
				glBegin(GL_QUADS);
					glTexCoord2f(queue[i]->tex_x1, queue[i]->tex_y1); glVertex2f(queue[i]->x1, queue[i]->y1);
					glTexCoord2f(queue[i]->tex_x2, queue[i]->tex_y1); glVertex2f(queue[i]->x2, queue[i]->y1);
					glTexCoord2f(queue[i]->tex_x2, queue[i]->tex_y2); glVertex2f(queue[i]->x2, queue[i]->y2);
					glTexCoord2f(queue[i]->tex_x1, queue[i]->tex_y2); glVertex2f(queue[i]->x1, queue[i]->y2);
				glEnd();
			}
/*			if (queue[i]->blend == 1)
			{
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				glBegin(GL_QUADS);
					glTexCoord2f(queue[i]->tex_x1, queue[i]->tex_y1); glVertex2f(queue[i]->x1, queue[i]->y1);
					glTexCoord2f(queue[i]->tex_x2, queue[i]->tex_y1); glVertex2f(queue[i]->x2, queue[i]->y1);
					glTexCoord2f(queue[i]->tex_x2, queue[i]->tex_y2); glVertex2f(queue[i]->x2, queue[i]->y2);
					glTexCoord2f(queue[i]->tex_x1, queue[i]->tex_y2); glVertex2f(queue[i]->x1, queue[i]->y2);
				glEnd();
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}*/
			glRotatef(-queue[i]->angle,0.0f,0.0f,1.0f);
			glTranslatef(-queue[i]->pos.x,-queue[i]->pos.y,-queue[i]->z);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	glTranslatef(ViewPos.x,ViewPos.y,0.0f);


	//освещение (пока тестово)
	if (_lights == true)
	{
		float lighting_r = 1.0f;
		float lighting_g = 0.949019608f;
		float lighting_b = 0.898039216f;

		int hour = minutes / 60;
		int mins = minutes - hour*60;
		float intens;
		int next_hour = hour + 1;
		if (next_hour > 23) next_hour -= 24;
		intens = day_intensity[hour]+(day_intensity[next_hour] - day_intensity[hour]) / 60 * mins;
	//	printf("time: %i:%i; light: %.3f\n",hour, mins,intens);

		float _r,_g,_b;
		_r = 0.02 * (0.615-intens) + lighting_r*intens;
		_g = 0.02 * (0.615-intens) + lighting_g*intens;
		_b = 0.05 * (0.615-intens) +lighting_b*intens;

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, shadow_buffer);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rboId);
	//	glClearColor(1, 1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, 0);

		glLoadIdentity();
		glTranslatef(-ViewPos.x,-ViewPos.y,0.0f);
	//	glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
		glColor3f(_r,_g,_b);
		glBegin(GL_QUADS);
			glVertex3f(-2048, -2048, 128);
			glVertex3f( 2048, -2048, 128);
			glVertex3f( 2048,  2048, 128);
			glVertex3f(-2048,  2048, 128);
		glEnd();

		glColor3f(1.0f,1.0f,1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		old_tex_id = 0;
		glTranslatef(0,0,128);
		float opos_x = 0, opos_y = 0;
		for (int i=0; i< lqueue_len; i++)
		{
			glColor4f(light_queue[i]->color.r, light_queue[i]->color.g, light_queue[i]->color.b, light_queue[i]->color.a * (1-intens*1.5));
			if (light_queue[i]->tex_id != old_tex_id)
			{
				glBindTexture(GL_TEXTURE_2D, light_queue[i]->tex_id);
				old_tex_id = light_queue[i]->tex_id;
			}
			glTranslatef(light_queue[i]->pos.x - opos_x,light_queue[i]->pos.y - opos_y,0);
			opos_x = light_queue[i]->pos.x;
			opos_y = light_queue[i]->pos.y;
			glRotatef(light_queue[i]->angle,0.0f,0.0f,1.0f);
			{
				glBegin(GL_QUADS);
					glTexCoord2f(0, 0); glVertex2f(light_queue[i]->x1, light_queue[i]->y1);
					glTexCoord2f(1, 0); glVertex2f(light_queue[i]->x2, light_queue[i]->y1);
					glTexCoord2f(1, 1); glVertex2f(light_queue[i]->x2, light_queue[i]->y2);
					glTexCoord2f(0, 1); glVertex2f(light_queue[i]->x1, light_queue[i]->y2);
				glEnd();
			}
			glRotatef(-light_queue[i]->angle,0.0f,0.0f,1.0f);
			//glTranslatef(-light_queue[i]->pos.x,-light_queue[i]->pos.y,0);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		}

		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

		glTranslatef(ViewPos.x,ViewPos.y,0.0f);
	//	glClearColor(0, 0, 0, 1);

		glBindTexture(GL_TEXTURE_2D, shadow_texid);
		glGenerateMipmapEXT(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		//рендер "теневого" буфера
		glLoadIdentity();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
	//	glTranslatef(-ViewPos.x,-ViewPos.y,0.0f);
		glBindTexture(GL_TEXTURE_2D, shadow_texid);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,				0.0f);				glVertex3f(-viewport_w/2, -512, 128);
			glTexCoord2f(float(window_width)/2048.0f,	0.0f);				glVertex3f(viewport_w/2, -512, 128);
			glTexCoord2f(float(window_width)/2048.0f,	float(window_height)/2048.0f);	glVertex3f(viewport_w/2,  512, 128);
			glTexCoord2f(0.0f,				float(window_height)/2048.0f);	glVertex3f(-viewport_w/2,  512, 128);
		glEnd();
	//	glTranslatef(ViewPos.x,ViewPos.y,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	clear_jobs();
}

void RenderManager::clear_jobs()
{
	for (int i=0; i< queue_len; i++)
	{
		free(queue[i]);
	}

	queue_len = 0;
	lqueue_len = 0;
	delete queue;
	queue = new job[queue_len];

	delete light_queue;
	light_queue = new ljob[lqueue_len];
}

void RenderManager::set_time(int time)
{
	minutes = time;
}
