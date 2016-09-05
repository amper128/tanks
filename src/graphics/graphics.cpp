#include <graphics/graphics.h>

TColor color(float r, float g, float b, float a)
{
	TColor c;
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return c;
}

TColor colori(int r, int g, int b, int a)
{
	TColor c;
	c.r = float(r)/255.0f;
	c.g = float(g)/255.0f;
	c.b = float(b)/255.0f;
	c.a = float(a)/255.0f;
	return c;
}

Texture LoadSpr(std::string filename)
{
	Texture tmp_spr;
	std::cout << "loading texture - " << filename << "... ";

	if (LoadTGA(&tmp_spr,filename))
	{
		glGenTextures(1, &tmp_spr.texID);
		glBindTexture(GL_TEXTURE_2D, tmp_spr.texID);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
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

/*void DrawGrid()
{
	glTranslatef(-ViewPos.x-32,-ViewPos.y+32,0.0f);

	glBindTexture(GL_TEXTURE_2D, grid.texID);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);					glVertex2f(0, 0);
		glTexCoord2f((float)(MAP.width-64)/256, 0.0f);			glVertex2f( MAP.width-64, 0);
		glTexCoord2f((float)(MAP.width-64)/256, (float)(MAP.height-64)/256);	glVertex2f( MAP.width-64,  MAP.height-64);
		glTexCoord2f(0.0f, (float)(MAP.height-64)/256);			glVertex2f(0,  MAP.height-64);
	glEnd();

	glTranslatef(ViewPos.x+32,ViewPos.y+32,0.0f);
}*/
