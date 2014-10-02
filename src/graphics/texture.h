#pragma once

#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library

struct TColor
{
	float r;
	float g;
	float b;
	float a;
};

TColor color(float r, float g, float b, float a=1)
{
	TColor c;
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return c;
}

TColor colori(int r, int g, int b, int a=255)
{
	TColor c;
	c.r = float(r)/255;
	c.g = float(g)/255;
	c.b = float(b)/255;
	c.a = float(a)/255;
	return c;
}

typedef struct
{
	GLuint	width;		// Image Width
	GLuint	height;		// Image Height
	GLuint	texID;
	GLint	orig_x;
	GLint	orig_y;

	int frames_x;
	int frames_y;
	int frame;

	bool	glob_texcoord;	//глобальность текстурных координат
	bool	part_texture;	//текстура целиком или ее куском натягивать
	//текстурные координаты у спрайта
	float	texcoord_x1;
	float	texcoord_x2;
	float	texcoord_y1;
	float	texcoord_y2;
} Sprite;

typedef	struct									
{
	GLubyte	* imageData;	// Image Data (Up To 32 Bits)
	GLuint	bpp;		// Image Color Depth In Bits Per Pixel
	GLuint	width;		// Image Width
	GLuint	height;		// Image Height
	GLuint	texID;		// Texture ID Used To Select A Texture
	GLuint	type;		// Image Type (GL_RGB, GL_RGBA)
} Texture;
