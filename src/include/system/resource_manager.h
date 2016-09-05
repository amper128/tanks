#pragma once

#include <map>
#include <system/strings.h>
#include <graphics/texture.h>
#include <system/vectors.h>

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
	TextureManager();

	static TextureManager& GetInstance()
	{
		static TextureManager _instance;
		return _instance;
	}

	void clear(void);

	Sprite* load(string filename, CPoint orig, int frames_x = 1, int frames_y = 1);
	Texture* find(string & name);
	string& basedir(void);

	~TextureManager();
};

class CResourceManager
{

};
