#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <memory.h>

#include "texture.h"

typedef struct
{
	GLubyte Header[12];	// TGA File Header
} TGAHeader;


typedef struct
{
	GLubyte		header[6];		// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;		// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;		// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;			// Temporary Variable
	GLuint		type;	
	GLuint		Height;			//Height of Image
	GLuint		Width;			//Width ofImage
	GLuint		Bpp;			// Bits Per Pixel
} TGA;

bool LoadTGA(Texture * texture, std::string filename);
bool LoadCompressedTGA(Texture * texture, std::string filename, FILE * fTGA);
bool LoadUncompressedTGA(Texture * texture, std::string filename, FILE * fTGA);
//#endif
