#include "projectile_bullet.h"
#include "effects.h"

TProjectileFire::TProjectileFire(Tpoint p, float angle, unsigned char type, unsigned char id)
{
	_type = oTypeBullet;
	_pos = p;
	_angle = angle;
	_speed = 5;

	std::string str;

	str = "projectiles/fire.tga";
	sprite = TexManager.load(str,point(0,0),2,2);

	_bounds = box(24,24);

	arm_dmg = 0.1f;
	expl_dmg = 1.0f;
	fire_dmg = 10;
	_height = 5;

	life_time = 100;
	fire_time = 50;
	_act = 0;
	_angle2 = float(rand()%3600)/10.0f;
}

void TProjectileFire::collide(TRigidBodyStatic * coll)
{
	if (coll->gettype() == oTypeTank || coll->gettype() == oTypeWater)
	{
		return;
		//if (((TProjectileFire*)coll)->pid() == 1)
		//{
		//	return;
		//}
	}
	if (_act == 0)
	{
		_act = 1;
		_speed = 0;
	}
	coll->damage(arm_dmg,expl_dmg);
	
//	printf("boom!\n");
//	destroy();
}

void TProjectileFire::step()
{
	_tmr++;
	if (_tmr >= 10)
	{
		sprite->frame++;
		_tmr = 0;
	}
	if (_height < 110)
		_height++;
	if (_bounds.w < 64)
	{
		_bounds.w++;
		_bounds.h++;
	}
	if (_act == 0)
	{
		_alpha -= 0.02f;
		if (_alpha <= 0)
			destroy();
		process();
	}
	else if (_act == 1)
	{
		fire_time--;
		if (fire_time < 200)
		{
			_alpha -= 0.005f;
		}
		if (_alpha <= 0)
			destroy();
	}
}

void TProjectileFire::destroy()
{
	_destroyed = true;
}

unsigned char TProjectileFire::pid()
{
	return player_id;
}

bool TProjectileFire::draw()
{
	render.draw(sprite, _pos, box(_bounds.w*2,_bounds.h*2), _angle2, _height,_alpha,1);
	render.draw_light(light_omni,_pos,box(_bounds.w*2,_bounds.h*2),0,colori(252,148,4,_alpha*255));
	return true;
}
