#pragma once

#include "vectors.h"
#include "keycodes.h"
;


bool keys_down[256];
bool keys_pressed[256];
char* kb_str;
int kb_str_sz;

bool keydown (const unsigned char key);
bool keyup (const unsigned char key);
bool keyhit (const unsigned char key);
Tpoint mouse_point();

void press_key (unsigned char key, int x, int y);
void up_key (unsigned char key, int x, int y);

void press_sp_key (int key, int x, int y);
void up_sp_key (int key, int x, int y);

void reset_keystate();

void MouseMoveFunc(int x, int y);
