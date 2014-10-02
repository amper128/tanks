#include "graphics.h"
#include "../system/vectors.h"
#include "../game/map.h"

void ViewPort(Tpoint pos)
{
	ViewPos = pos;
	if (MAP.width+64 < viewport_w)
	{
		ViewPos.x = MAP.width/2;
	}
	else
	{
		ViewPos.x = max(ViewPos.x,viewport_w/2-32);
		ViewPos.x = min(ViewPos.x,MAP.width-viewport_w/2+32);
	}

	if (MAP.height+64 < viewport_h)
	{
		ViewPos.y = MAP.height/2;
	}
	else
	{
		ViewPos.y = max(ViewPos.y,viewport_h/2-32);
		ViewPos.y = min(ViewPos.y,MAP.height-viewport_h/2+32);
	}
//	
//	ViewPos.y = max(ViewPos.y,viewport_h/2-32);

//	V
//	ViewPos.y = min(ViewPos.y,MAP.height-viewport_h/2+32);
}

void draw_sprite(Sprite* tex, Tpoint pos, float angle)
{
	glTranslatef(pos.x-ViewPos.x,pos.y-ViewPos.y,0.0f);
	glRotatef(angle,0.0f,0.0f,1.0f);

	glBindTexture(GL_TEXTURE_2D, tex->texID);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(-(GLfloat)tex->width/2+tex->orig_x, -(GLfloat)tex->height/2+tex->orig_y);
		glTexCoord2f(1.0f, 0.0f); glVertex2f( (GLfloat)tex->width/2+tex->orig_x, -(GLfloat)tex->height/2+tex->orig_y);
		glTexCoord2f(1.0f, 1.0f); glVertex2f( (GLfloat)tex->width/2+tex->orig_x,  (GLfloat)tex->height/2+tex->orig_y);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-(GLfloat)tex->width/2+tex->orig_x,  (GLfloat)tex->height/2+tex->orig_y);
	glEnd();
	glRotatef(-angle,0.0f,0.0f,1.0f);
	glTranslatef(-(pos.x-ViewPos.x),-(pos.y-ViewPos.y),0.0f);
}

Texture LoadSpr(string filename)
{
	Texture tmp_spr;
	std::cout << "loading texture - " << filename << "... ";

	if (LoadTGA(&tmp_spr,filename))
	{
		glGenTextures(1, &tmp_spr.texID);
		glBindTexture(GL_TEXTURE_2D, tmp_spr.texID);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST_MIPMAP_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, tmp_spr.bpp / 8, tmp_spr.width, tmp_spr.height, 0, tmp_spr.type, GL_UNSIGNED_BYTE, tmp_spr.imageData);
		std::cout << "\n";
		return tmp_spr;
	}
	else
	{
		printf("texture not loaded!\n");
	}
}

void DrawTanks()
{
	
}

void DrawGrid()
{
	glTranslatef(-ViewPos.x-32,-ViewPos.y-32,0.0f);

	glBindTexture(GL_TEXTURE_2D, grid.texID);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);					glVertex2f(0, 0);
		glTexCoord2f((float)MAP.width/256, 0.0f);			glVertex2f( MAP.width, 0);
		glTexCoord2f((float)MAP.width/256, (float)MAP.height/256);	glVertex2f( MAP.width,  MAP.height);
		glTexCoord2f(0.0f, (float)MAP.height/256);			glVertex2f(0,  MAP.height);
	glEnd();

	glTranslatef(ViewPos.x+32,ViewPos.y+32,0.0f);
}

void DrawDecals()
{
	if (!MAP.decals.empty())
	{
		glBindTexture(GL_TEXTURE_2D, decal_spr.texID);
		std::list<object_2d*>::iterator element;
//		object_2d *dec;

		float cos1;
		float sin1;

		glTranslatef(-ViewPos.x,-ViewPos.y,0.0f);
		glBegin(GL_QUADS);
		for (element = MAP.decals.begin (); element != MAP.decals.end (); element++)
		{
			//trac = (*element);
			if (((*element)->pos().x - viewport_w/2 - 64 <= ViewPos.x) && ((*element)->pos().x + viewport_w/2 + 64 >= ViewPos.x)
			&& ((*element)->pos().y - viewport_h/2 - 64 <= ViewPos.y) && ((*element)->pos().y + viewport_h/2 + 64 >= ViewPos.y))
			{
				glColor4f(1.0f,1.0f,1.0f,(*element)->alpha());
				cos1 = Cos((*element)->angle());
				sin1 = Sin((*element)->angle());
				
				//glRotatef((*element)->angle,0.0f,0.0f,1.0f);
					
					glTexCoord2f(1.0f, 0.0f); glVertex2f((*element)->pos().x+8*cos1+8*sin1, (*element)->pos().y+8*sin1-8*cos1);
					glTexCoord2f(1.0f, 1.0f); glVertex2f((*element)->pos().x+8*cos1-8*sin1, (*element)->pos().y+8*sin1+8*cos1);
					glTexCoord2f(0.0f, 1.0f); glVertex2f((*element)->pos().x-8*cos1-8*sin1, (*element)->pos().y-8*sin1+8*cos1);
					glTexCoord2f(0.0f, 0.0f); glVertex2f((*element)->pos().x-8*cos1+8*sin1, (*element)->pos().y-8*sin1-8*cos1);
				
				//glRotatef(-(*element)->angle,0.0f,0.0f,1.0f);
			}
		}
		glEnd();
		glTranslatef(ViewPos.x,ViewPos.y,0.0f);
	
/*
		Tdecal trac;
		int dec_id;
		dec_id = MAP.trac_decals.first_id();
		while (dec_id != -1)
		{
			trac = MAP.trac_decals.get(dec_id);
			if (((*element)->pos.x - viewport_w/2 - 64 <= ViewPos.x) && ((*element)->pos.x + viewport_w/2 + 64 >= ViewPos.x)
			&& ((*element)->pos.y - viewport_h/2 - 64 <= ViewPos.y) && ((*element)->pos.y + viewport_h/2 + 64 >= ViewPos.y))
			{
				glTranslatef((*element)->pos.x-ViewPos.x,(*element)->pos.y-ViewPos.y,0.0f);
				glRotatef((*element)->angle,0.0f,0.0f,1.0f);
				glBegin(GL_QUADS);
					glColor4f(1.0f,1.0f,1.0f,(*element)->alpha);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-8, -8,  0.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f( 8, -8,  0.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f( 8,  8,  0.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(-8,  8,  0.0f);
				glEnd();
				glRotatef(-(*element)->angle,0.0f,0.0f,1.0f);
				glTranslatef(-((*element)->pos.x-ViewPos.x),-((*element)->pos.y-ViewPos.y),0.0f);
			}
			dec_id = MAP.trac_decals.next_id(dec_id);
		}
		*/
		glColor4f(1.0f,1.0f,1.0f,1.0f);
		
	}
}

void DrawObjects()
{
	int old_tex_id = 0;
	float old_angle = 0;

	if (!MAP.statics.empty())
	{
		std::list<TRigidBodyStatic*>::iterator element, end;

		TRigidBodyStatic* obj;
		end = MAP.statics.end();
		for (element = MAP.statics.begin (); element != end; element++)
		{
			obj = (*element);
			if ((obj->pos().x - viewport_w/2 - 128 <= ViewPos.x) && (obj->pos().x + viewport_w/2 + 128 >= ViewPos.x)
			&& (obj->pos().y - viewport_h/2 - 128 <= ViewPos.y) && (obj->pos().y + viewport_h/2 + 128 >= ViewPos.y))
			{
				if (!obj->draw())
				{
/*					if ((*element)->sprite->texID != old_tex_id)
					{
						glBindTexture(GL_TEXTURE_2D, (*element)->sprite->texID);
						old_tex_id = (*element)->sprite->texID;
					}
					glTranslatef((*element)->pos().x-ViewPos.x,(*element)->pos().y-ViewPos.y,0.0f);
					glRotatef((*element)->angle(),0.0f,0.0f,1.0f);
					glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex2f(-(*element)->bounds().w/2, -(*element)->bounds().h/2);
						glTexCoord2f(1.0f, 0.0f); glVertex2f( (*element)->bounds().w/2, -(*element)->bounds().h/2);
						glTexCoord2f(1.0f, 1.0f); glVertex2f( (*element)->bounds().w/2,  (*element)->bounds().h/2);
						glTexCoord2f(0.0f, 1.0f); glVertex2f(-(*element)->bounds().w/2,  (*element)->bounds().h/2);
					glEnd();
					glRotatef(-(*element)->angle(),0.0f,0.0f,1.0f);
					glTranslatef(-((*element)->pos().x-ViewPos.x),-((*element)->pos().y-ViewPos.y),0.0f);*/
					render.draw(obj->sprite, obj->pos(), obj->bounds(), obj->angle(), obj->height());
				}
			}
		}
		
	}

	if (!MAP.dynamics.empty())
	{
		std::list<TRigidBodyDynamic*>::iterator element, end;

		TRigidBodyDynamic* dyn;
		end = MAP.dynamics.end();
		for (element = MAP.dynamics.begin (); element != end; element++)
		{
			dyn = (*element);
			//if ((dyn->pos().x - viewport_w/2 - 128 <= ViewPos.x) && (dyn->pos().x + viewport_w/2 + 128 >= ViewPos.x)
			//&& (dyn->pos().y - viewport_h/2 - 128 <= ViewPos.y) && (dyn->pos().y + viewport_h/2 + 128 >= ViewPos.y))
			{
				if (!dyn->draw())
				{
/*					if ((*element)->sprite->texID != old_tex_id)
					{
						old_tex_id = (*element)->sprite->texID;
						glBindTexture(GL_TEXTURE_2D, old_tex_id);
					}
					glTranslatef((*element)->pos().x-ViewPos.x,(*element)->pos().y-ViewPos.y,0.0f);
					glRotatef((*element)->angle(),0.0f,0.0f,1.0f);
					glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex2f(-(*element)->bounds().w/2, -(*element)->bounds().h/2);
						glTexCoord2f(1.0f, 0.0f); glVertex2f( (*element)->bounds().w/2, -(*element)->bounds().h/2);
						glTexCoord2f(1.0f, 1.0f); glVertex2f( (*element)->bounds().w/2,  (*element)->bounds().h/2);
						glTexCoord2f(0.0f, 1.0f); glVertex2f(-(*element)->bounds().w/2,  (*element)->bounds().h/2);
					glEnd();
					glRotatef(-(*element)->angle(),0.0f,0.0f,1.0f);
					glTranslatef(-((*element)->pos().x-ViewPos.x),-((*element)->pos().y-ViewPos.y),0.0f);*/
					render.draw(dyn->sprite, dyn->pos(), dyn->bounds(), dyn->angle(), dyn->height());
				}
			}
		}
		
	}

	if (!MAP.objects_2d.empty())
	{
		std::list<object_2d*>::iterator element, end;

		object_2d* o2d;
		end = MAP.objects_2d.end();
		for (element = MAP.objects_2d.begin (); element != end; element++)
		{
			o2d = (*element);
			if ((o2d->pos().x - viewport_w/2 - 128 <= ViewPos.x) && (o2d->pos().x + viewport_w/2 + 128 >= ViewPos.x)
			&& (o2d->pos().y - viewport_h/2 - 128 <= ViewPos.y) && (o2d->pos().y + viewport_h/2 + 128 >= ViewPos.y))
			{
				if (!o2d->draw())
				{
					render.draw(o2d->sprite, o2d->pos(), o2d->size(), o2d->angle(), o2d->height());
				}
			}
		}
		
	}
}

/*void DrawLights(int minutes = 12*60, float lighting_r = 1.0f, float lighting_g = 0.949019608f, float lighting_b = 0.898039216f)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glTranslatef(-ViewPos.x,-ViewPos.y,0.0f);
	glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);

	int hour = minutes / 60;
	int mins = minutes - hour*60;
	float intens;
	int next_hour = hour + 1;
	if (next_hour > 23) next_hour -= 24;
	intens = day_intensity[hour]+(day_intensity[next_hour] - day_intensity[hour]) / 60 * mins;
	printf("time: %i:%i; light: %.3f\n",hour, mins,intens);

	float _r,_g,_b;
	_r = 0.05 * (0.615-intens) + lighting_r*intens;
	_g = 0.05 * (0.615-intens) + lighting_g*intens;
	_b = 0.1 * (0.615-intens) +lighting_b*intens;

	glColor3f(_r,_g,_b);
	glTranslatef(-ViewPos.x,-ViewPos.y,0.0f);
	glBegin(GL_QUADS);
		glVertex3f(-2048, -2048, 128);
		glVertex3f( 2048, -2048, 128);
		glVertex3f( 2048,  2048, 128);
		glVertex3f(-2048,  2048, 128);
	glEnd();

	glColor3f(1.0f,1.0f,1.0f);
	glTranslatef(ViewPos.x,ViewPos.y,0.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}*/

void DrawLand()
{
	float x1,y1,x2,y2;
	float _x1,_y1,_x2,_y2;
	glTranslatef(-ViewPos.x,-ViewPos.y,0.0f);

	glBindTexture(GL_TEXTURE_2D, grounds[0].texID);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);					glVertex2f(0, 0);
		glTexCoord2f((float)MAP.width/256, 0.0f);			glVertex2f( MAP.width, 0);
		glTexCoord2f((float)MAP.width/256, (float)MAP.height/256);	glVertex2f( MAP.width,  MAP.height);
		glTexCoord2f(0.0f, (float)MAP.height/256);			glVertex2f(0,  MAP.height);
	glEnd();

	glTranslatef(-64,0.0f,0.0f);
	for (int mat=1; mat < 16; mat++)
	{
		glBindTexture(GL_TEXTURE_2D, grounds[mat].texID);

		for (int i = 1; i < MAP.width/64+1; i++)
		{
			for (int j = 1; j < MAP.height/64+1; j++)
			{
				if ((i*64 - viewport_w/2 - 128 <= ViewPos.x) && (i*64 + viewport_w/2 + 128 >= ViewPos.x) 
				&& (j*64 - viewport_h/2 - 128 <= ViewPos.y) && (j*64 + viewport_h/2 + 128 >= ViewPos.y))
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
						if (MAP.map[i][j] == mat)
						{
							//серединка
							glColor4f(1.0f,1.0f,1.0f,1.0f);
							glTexCoord2f(x1, y1); glVertex2f(_x1, _y1);
							glTexCoord2f(x2, y1); glVertex2f(_x2, _y1);
							glTexCoord2f(x2, y2); glVertex2f(_x2, _y2);
							glTexCoord2f(x1, y2); glVertex2f(_x1, _y2);

							//нижний левый угол
							if (MAP.map[i][j-1] != mat && MAP.map[i-1][j] != mat)
							{
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1-0.125, 	y1);		glVertex2f(_x1-32, _y1);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1-0.125, 	y1-0.125);	glVertex2f(_x1-32, _y1-32);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1, 	y1-0.125);	glVertex2f(_x1, _y1-32);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x1, 	y1);		glVertex2f(_x1, _y1);
							}

							//левый бок
							if (MAP.map[i-1][j] != mat)
							{
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1-0.125,	y1);	glVertex2f(_x1-32, _y1);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x1, 	y1);	glVertex2f(_x1, _y1);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x1, 	y2);	glVertex2f(_x1, _y2);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1-0.125,	y2);	glVertex2f(_x1-32, _y2);
							}

							//левый верхний угол
							if (MAP.map[i][j+1] != mat && MAP.map[i-1][j] != mat)
							{
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1-0.125,	y2);		glVertex2f(_x1-32, _y2);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x1, 	y2);		glVertex2f(_x1, _y2);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1,	y2+0.125f);	glVertex2f(_x1, _y2+32);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1-0.125,	y2+0.125f);	glVertex2f(_x1-32, _y2+32);
							}

							//правый нижний угол
							if (MAP.map[i][j-1] != mat && MAP.map[i+1][j] != mat)
							{
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2+0.125f,	y1);		glVertex2f(_x2+32, _y1);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x2,	y1);		glVertex2f(_x2, _y1);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2,	y1-0.125f);	glVertex2f(_x2, _y1-32);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2+0.125f,	y1-0.125f);	glVertex2f(_x2+32, _y1-32);
							}

							//правый бок
							if (MAP.map[i+1][j] != mat)
							{
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2+0.125f, y2);		glVertex2f(_x2+32, _y2);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x2, 	y2);		glVertex2f(_x2, _y2);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x2, 	y1);		glVertex2f(_x2, _y1);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2+0.125f, y1);		glVertex2f(_x2+32, _y1);
							}

							//верхний правый угол
							if (MAP.map[i][j+1] != mat && MAP.map[i+1][j] != mat)
							{
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2+0.125f, y2);	glVertex2f(_x2+32, _y2);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x2, y2);	glVertex2f(_x2, _y2);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2, y2+0.125);	glVertex2f(_x2, _y2+32);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2+0.125f, y2+0.125);	glVertex2f(_x2+32, _y2+32);
							}

							//верхушка
							if (MAP.map[i][j+1] != mat)
							{
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x2, y2);	glVertex2f(_x2, _y2);
								glColor4f(1.0f,1.0f,1.0f,1.0f);	glTexCoord2f(x1, y2);	glVertex2f(_x1, _y2);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x1, y2+0.125f);	glVertex2f(_x1, _y2+32);
								glColor4f(1.0f,1.0f,1.0f,0.0f);	glTexCoord2f(x2, y2+0.125f);	glVertex2f(_x2, _y2+32);
							}

							//подвал
							if (MAP.map[i][j-1] != mat)
							{
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

	glTranslatef(ViewPos.x+64,ViewPos.y,0.0f);
}
