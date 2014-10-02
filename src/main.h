#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

//ядро движка
#include "system/system.cpp"
#include "system/vectors.cpp"

#include "global.cpp"
#include "game/map.cpp"

#include "graphics/tga.cpp"
#include "graphics/graphics.cpp"
#include "graphics/render_manager.cpp"

#include "game/rigid_body_static.cpp"
#include "game/object_water.cpp"
#include "game/wall_brick.cpp"
#include "game/wall_beton.cpp"

#include "game/object_2d.cpp"
#include "game/object_decal.cpp"
#include "game/object_tree.cpp"

#include "game/effects.cpp"

#include "game/rigid_body_dynamic.cpp"
#include "game/object_tank.cpp"
#include "game/projectile_bullet.cpp"
#include "game/projectile_fire.cpp"

//#include "game/game.cpp"

void stepgame();
void drawgame();
bool gameloop();
