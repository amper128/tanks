#pragma once

#include <string>
#include <map>

#include <graphics/texture.h>
#include <graphics/tga.h>
#include <system/vectors.h>

typedef struct
{
	float r;
	float g;
	float b;
	float a;
} TColor;

TColor color(float r, float g, float b, float a=1);

TColor colori(int r, int g, int b, int a=255);

void draw_sprite(Sprite* tex, CPoint pos, float angle);
Texture LoadSpr(std::string filename);
