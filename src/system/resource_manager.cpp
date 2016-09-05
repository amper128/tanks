#include <system/resource_manager.h>
#include <graphics/graphics.h>

TextureManager::TextureManager() {
	m_base_dir = "gamedata/textures";
}

string& TextureManager::basedir(void) {
	return m_base_dir;
}

void TextureManager::clear(void) {
	obj_map::iterator i;

	for (i = m_map.begin(); i != m_map.end(); i++) {
		Texture* o = (*i).second;
		glDeleteTextures(1, &o->texID);
		delete o;
	}

	m_map.clear();
}

Sprite * TextureManager::load(string filename, CPoint orig, int frames_x, int frames_y)
{
	Texture* o = find(filename);
	Sprite* ret;
	ret = new Sprite;

	if (o == NULL) {
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

	ret->width = o->width;
	ret->height = o->height;

	return ret;
}

Texture * TextureManager::find(string& name)
{
	obj_map::iterator	i;
	i = m_map.find(name);
	if(i==m_map.end()) return NULL;
	return ((*i).second);
}

TextureManager::~TextureManager() {
	clear();
}
