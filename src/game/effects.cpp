#include "effects.h"

TExplo::TExplo(Tpoint pos, unsigned char dmg, unsigned char id)
{
	_pos = pos;
	std::string str;
	str = "effects/explosion_2.tga";
	sprite = TexManager.load(str,point(0,0),4,4);
	sprite->frame = 0;
	_bounds = box(16,16);
	_height = 110;

	cur_dmg = 80;

	_angle = float(rand() % 3600) / 10.0f;
	lightning = 0;
}

void TExplo::step()
{
	cur_dmg--;
	if (cur_dmg > 0)
	{
		_tmr++;
		if (_tmr >= 5)
		{
			sprite->frame++;
			_tmr = 0;
		}
		_bounds = box(96-cur_dmg,96-cur_dmg);

		if (sprite->frame < 5)
		{
			lightning += 0.05;
		}
		else
		{
			lightning -= 0.03;
		}
	}
	else
	{
		_destroyed = true;
	}
	
}

void TExplo::collide(TRigidBodyStatic* body)
{
	body->damage(0,1);
//	printf("oops!\n");
}

bool TExplo::draw()
{
	render.draw(sprite, _pos, box(128,128), _angle, _height,1.0f,1);
	render.draw_light(light_omni,_pos,box(128,128),0,colori(250,158,11,lightning*255));
	return true;
}

TExplo2::TExplo2(Tpoint pos, unsigned char dmg, unsigned char id)
{
	_pos = pos;
	std::string str;
	str = "effects/explosion_1.tga";
	sprite = TexManager.load(str,point(0,0),4,4);
	sprite->frame = 0;
	_bounds = box(16,16);
	_height = 110;

	cur_dmg = 160;

	_angle = float(rand() % 3600) / 10.0f;
	lightning = 0;
}

void TExplo2::step()
{
	cur_dmg--;
	if (sprite->frame <15 && cur_dmg >= 0)
	{
		_tmr++;
		if (_tmr >= 10)
		{
			sprite->frame++;
			_tmr = 0;
		}
		_bounds = box(160-cur_dmg,160-cur_dmg);

		if (sprite->frame < 5)
		{
			lightning += 0.025;
		}
		else
		{
			lightning -= 0.015;
		}
	}
	else
	{
		destroy();
	}
	
}

void TExplo2::collide(TRigidBodyStatic* body)
{
	body->damage(0,2);
//	printf("oops!\n");
}

bool TExplo2::draw()
{
	render.draw(sprite, _pos, box(192,192), _angle, _height,1.0f,1);
	render.draw_light(light_omni,_pos,box(192,192),0,colori(255,158,11,lightning*255));
	return true;
}
