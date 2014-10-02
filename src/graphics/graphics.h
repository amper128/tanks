#pragma once
#include "texture.h"
#include "render_manager.h"
#include <string>
#include <map>

Texture decal_spr;
Texture tree_spr;
Texture beton_spr;
Texture *grounds;
Texture grid;

Sprite* light_omni;
Sprite* light_spot;

float day_intensity[24] = {
0.0f, 0.0f, 0.0f, 0.0f, 0.00002f,					//ночь
0.1567f, 0.3505f, 0.46136f, 0.52626f, 0.56592f,				//утро
0.59034f, 0.6046f, 0.6112f, 0.61124f, 0.60468f, 0.59048f, 0.56614f,	//день
0.52662f, 0.46198f, 0.35158f, 0.1585f,					//вечер
0.00002f, 0.0f, 0.0f							//снова ночь
};

float viewport_w, viewport_h;

void draw_sprite(Sprite* tex, Tpoint pos, float angle);
Texture LoadSpr(string filename);

Tpoint ViewPos;

GLuint shadow_buffer = 0;
GLuint shadow_texid = 0;
GLuint rboId = 0;

class TextureManager
{
//public:
	//typedef Type	obj_type;
	//typedef Type * ref_type;
	typedef std::map<string, Texture*> obj_map;
private:
	obj_map	m_map;
	string	m_base_dir;
public:
	TextureManager(void){
		m_base_dir = "gamedata/textures";
	};

	~TextureManager(void){ clear(); };

	void clear(void) {
		obj_map::iterator	i;
		for(i = m_map.begin(); i!=m_map.end(); i++){
			Texture* o = (*i).second;
			delete o;
		}
		m_map.clear();
	};

	Sprite* load(string & filename, Tpoint orig, int frames_x = 1, int frames_y = 1)
	{
		Texture* o = find(filename);
		Sprite* ret;
		ret = new Sprite;
		if(o==NULL) {
			o = new Texture();
			*o = LoadSpr(m_base_dir + "/" + filename);
			//if(!o->load(m_base_dir + "\\" + filename)){
			//	delete o;
			//	o = NULL;
			//}
			m_map.insert(obj_map::value_type(filename, o));
		}
		ret->orig_x = orig.x;
		ret->orig_y = orig.y;
		ret->frames_x = frames_x;
		ret->frames_y = frames_y;
		ret->frame = 0;
		ret->texID = o->texID;

		return ret;
	};

	Texture* find(string & name){
		obj_map::iterator	i;
		i = m_map.find(name);
		if(i==m_map.end()) return NULL;
		return ((*i).second);
	};
	string & basedir(void){ return m_base_dir; };
};

TextureManager TexManager;
