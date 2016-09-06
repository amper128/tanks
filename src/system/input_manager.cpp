#include <system/input_manager.h>

CInputManager& CInputManager::GetInstance()
{
	static CInputManager _instance;
	return _instance;
}

int CInputManager::translate_keycode(int key)
{
	switch (key) {
	case 97:
		return VK_A;
	case 98:
		return VK_B;
	case 99:
		return VK_C;
	case 100:
		return VK_D;
	case 101:
		return VK_E;
	case 102:
		return VK_F;
	case 103:
		return VK_G;
	case 104:
		return VK_H;
	case 105:
		return VK_I;
	case 106:
		return VK_J;
	case 107:
		return VK_K;
	case 108:
		return VK_L;
	case 109:
		return VK_M;
	case 110:
		return VK_N;
	case 111:
		return VK_O;
	case 112:
		return VK_P;
	case 113:
		return VK_Q;
	case 114:
		return VK_R;
	case 115:
		return VK_S;
	case 116:
		return VK_T;
	case 117:
		return VK_U;
	case 118:
		return VK_V;
	case 119:
		return VK_W;
	case 120:
		return VK_X;
	case 121:
		return VK_Y;
	case 122:
		return VK_Z;
	case 273:
		return VK_UP;
	case 274:
		return VK_DOWN;
	case 275:
		return VK_RIGHT;
	case 276:
		return VK_LEFT;
	case 282:
		return VK_F1;
	case 283:
		return VK_F2;
	case 284:
		return VK_F3;
	case 285:
		return VK_F4;
	case 286:
		return VK_F5;
	case 287:
		return VK_F6;
	case 288:
		return VK_F7;
	case 289:
		return VK_F8;
	case 290:
		return VK_F9;
	case 291:
		return VK_F10;
	case 292:
		key = VK_F11;
	case 293:
		return VK_F12;
	}
	return key;
}

void CInputManager::press_key (int key_code, int /*x*/, int /*y*/)
{
	int key = translate_keycode(key_code);

	if (!keys_down[key]) {
		keys_pressed[key] = true;
	}
	keys_down[key] = true;
//	keys_pressed[key] = true;

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

void CInputManager::up_key (int key_code, int /*x*/, int /*y*/)
{
	int key = translate_keycode(key_code);
	keys_down[key] = false;
}

void CInputManager::reset_keystate()
{
	for (int i = 0; i < 300; i++) {
		keys_pressed[i] = false;
	}
}

void CInputManager::mouse_move(float x, float y)
{
	mouse_point.x = x;
	mouse_point.y = y;
}

bool CInputManager::keydown (int key)
{
	return keys_down[key];
}

bool CInputManager::keyup (int key)
{
	if (!keys_down[key]) {
		return keys_pressed[key];
	}

	return false;
}

bool CInputManager::keyhit (int key)
{
	return keys_pressed[key];
}
