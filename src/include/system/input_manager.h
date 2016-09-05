#pragma once

#include <map>

#include <system/vectors.h>
#include <system/keycodes.h>

class CInputManager
{
private:
	bool keys_down[300];
	bool keys_pressed[300];
	char * kb_str;
	int kb_str_sz;
	CVector mouse_point;

	int translate_keycode(int key);
public:
	static CInputManager& GetInstance();

	bool keydown (int key);
	bool keyup (int key);
	bool keyhit (int key);

	void press_key (int key, int x, int y);
	void up_key (int key, int x, int y);

	void press_sp_key (int key, int x, int y);
	void up_sp_key (int key, int x, int y);

	void reset_keystate(void);

	void mouse_move(float x, float y);
};
