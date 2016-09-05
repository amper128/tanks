#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

//ядро движка
#include "system/system.h"
#include "system/vectors.h"

#include "global.h"
#include "game/SCMap.h"

#include "graphics/tga.h"
#include "graphics/graphics.h"
#include "graphics/render_manager.h"
#include "graphics/fonts.h"

//#include "graphics/window.h"

#include "gui/GUI.h"

/*//основные интерфейсы объектов
#include "game/IObjectBase.h"
#include "game/IObject2D.h"
#include "game/IObjectStatic.h"
#include "game/IObjectDynamic.h"
#include "game/IVehicleBase.h"

//типы объектов
#include "game/GCObjectWater.h"
#include "game/GCObjectBrick.h"
#include "game/GCObjectBeton.h"

//FIXME: rename files
#include "game/object_decal.h"
#include "game/GCObjectTree.h"

#include "game/effects.h"

#include "game/GCVehicleMiddleTank.h"
#include "game/projectile_bullet.h"
#include "game/projectile_fire.h"

//#include "game/game.cpp"*/
