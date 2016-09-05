#include <graphics/fonts.h>
#include <graphics/render_manager.h>
#include <fstream>
#include <system/strings.h>

TFont::TFont()
{
	for (int i = 0; i < 256; i++) {
		xpos[i] = 0;
		ypos[i] = 0;
		chrw[i] = 0;
		chrh[i] = 0;
		yoffs[i] = 0;
	}
}

void TFont::LoadFont(std::string name)
{
	TextureManager& TexManager = TextureManager::GetInstance();
	std::ifstream in(("gamedata/textures/gui/"+name+".fnt").c_str());
	string line;
	string font_file = "gui/" + name + ".tga";

	int tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0, tmp5 = 0, tmp6 = 0;

	if (in) {
		while (std::getline(in, line)) {
			if (sscanf(line.c_str(), "%i\t%i\t%i\t%i\t%i\t%i", &tmp1, &tmp2, &tmp3, &tmp4, &tmp5, &tmp6)) {
				xpos[tmp1] = tmp2;
				ypos[tmp1] = tmp3;

				chrw[tmp1] = tmp4;
				chrh[tmp1] = tmp5;

				yoffs[tmp1] = tmp6;
			}
		}

		fnt_sprite = TexManager.load(font_file, point(0, 0));
	}
}

void TFont::DrawStringCenter(std::string text, float x, float y,  TColor col)
{
	x -= int(StringWidth(text) / 2);
	DrawString(text,x,y, col);
}

void TFont::DrawString(std::string text, float x, float y, TColor col)
{
	CRenderManager& render = CRenderManager::GetInstance();
	float pos_x = x, pos_y = y;
	float fw, fh;
	float x1, y1, x2, y2, w, h;
	float px1, py1, px2, py2;
	unsigned char ind;

	glLoadIdentity();

	fw = fnt_sprite->width;
	fh = fnt_sprite->height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, render.wnd_width, render.wnd_height, 0, -128, 256);
	glMatrixMode(GL_MODELVIEW);

	glBindTexture(GL_TEXTURE_2D, fnt_sprite->texID);
	glColor4f(col.r,col.g,col.b,col.a);
	glBegin(GL_QUADS);

	for (size_t i = 0; i < text.length(); i++) {
		ind = text[i];
		x1 = xpos[ind];
		y1 = -ypos[ind];

		w = chrw[ind];
		h = chrh[ind];

		x2 = x1 + w;
		y2 = y1 + h;

		px1 = pos_x;
		px2 = pos_x + w;
		py1 = pos_y - h - yoffs[ind];
		py2 = pos_y - yoffs[ind];

		glTexCoord2f(x1/fw, y2/fh);	glVertex2f(px1, py1);
		glTexCoord2f(x2/fw, y2/fh);	glVertex2f(px2, py1);
		glTexCoord2f(x2/fw, y1/fh);	glVertex2f(px2, py2);
		glTexCoord2f(x1/fw, y1/fh);	glVertex2f(px1, py2);

		pos_x += w;
	}
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glViewport(0, 0, render.wnd_width, render.wnd_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-render.ViewSize().w / 2, render.ViewSize().w / 2, -render.ViewSize().h / 2, render.ViewSize().h / 2, -128, 256);
	glMatrixMode(GL_MODELVIEW);
}

float TFont::StringWidth(std::string text)
{
	float res = 0;

	for (size_t i = 0; i < text.length(); i++) {
		res += chrw[(unsigned char)text[i]];
	}

	return res;
}

TFont::~TFont()
{

}
