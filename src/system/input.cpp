#include "input.h"

void press_key (unsigned char key_code, int x, int y)
{
	char key = key_codes[key_code];
	keys_down[key] = true;
	keys_pressed[key] = true;

	//if (key_code > 31)
	//{
	//	char *tmp;
	//	tmp = kb_str;
//
//		kb_str_sz++;
//		kb_str = new char[kb_str_sz];
//
//		for (int i=0; i<kb_str_sz; i++)
//		{
//			kb_str[i] = tmp[i];
//		}
//		kb_str[kb_str_sz] = key_code;
//	}
}

void up_key (unsigned char key_code, int x, int y)
{
	char key = key_codes[key_code];
	keys_down[key] = false;
}

void press_sp_key (int key_code, int x, int y)
{
	char key = key_sp_codes[key_code];
	keys_down[key] = true;
	keys_pressed[key] = true;
}

void up_sp_key (int key_code, int x, int y)
{
	char key = key_sp_codes[key_code];
	keys_down[key] = false;
}

void reset_keystate()
{
	for (int i = 0; i<256; i++)
		keys_pressed[i] = false;
}

/*void MouseMoveFunc(int x, int y)
{
	mouse_pos.x = (x - window_width/2)/win_to_map_x*2;
	mouse_pos.y = (y - window_height/2)/win_to_map_y*2;
}*/
