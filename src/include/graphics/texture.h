#pragma once
#define GL_GLEXT_PROTOTYPES
#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library

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
