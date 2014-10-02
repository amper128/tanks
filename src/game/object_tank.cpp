#include "object_tank.h"
#include "map.h"
//#include "wall.h"

TWeapon::~TWeapon()
{

}

void TWeapon::step()
{
	switch (rotation)
	{
	default:
		if (rotation_speed > 0.05) rotation_speed -= 0.05;
		if (rotation_speed < -0.05) rotation_speed += 0.05;
		if (fabs(rotation_speed) < 0.05) rotation_speed = 0;
		break;
	case 1:
		if (rotation_speed < -0.05) rotation_speed += 0.05;
		else rotation_speed = min(rotation_speed+0.02,1.0);
		break;
	case 2:
		if (rotation_speed > 0.05) rotation_speed -= 0.05;
		else rotation_speed = max(rotation_speed-0.02,-1.0);
		break;
	}
	cur_angle += rotation_speed;

	if (!can_shot)
	{
		shot_timer++;
		if (shot_timer >= 5)
			can_shot = true;
	}
}

void TWeapon::setpos(Tpoint p)
{
	pos = p;
}

Tpoint TWeapon::getpos()
{
	return pos;
}

void TWeapon::setangle(float angle)
{
	cur_angle = angle;
}

void TWeapon::setpotangle(float angle)
{
	pot_angle = angle;
}

float TWeapon::getangle()
{
	return cur_angle;
}

void TWeapon::shot()
{
	if (can_shot)
	{
		//TBullet *bullet;
		TProjectileFire* bullet;
		Tpoint np;
		np.x = pos.x - 76*Sin(cur_angle);
		np.y = pos.y + 76*Cos(cur_angle);
		bullet = new TProjectileFire(np,cur_angle+float(rand() % 100 - 50)/5,1,1);
		//bullet = new TBullet(np,cur_angle,1,1);
		MAP.dynamics.push_back(bullet);
		can_shot = false;
		shot_timer = 0;
	}
}

void TWeapon::setrotation(unsigned char rot)
{
	rotation = rot;
}

void TTank::kill()
{
	if (alive)
	{
		alive = false;
		killtime = 0;
		std::cout << "player was killed!\n";
		killed = true;

		TExplo2* explosion;
		explosion = new TExplo2(_pos,32,1);
		MAP.dynamics.push_back(explosion);

		explosion = new TExplo2(_pos,32,1);
		MAP.dynamics.push_back(explosion);
	}
}

void TTank::resurrect()
{
	health = 100;
	arm = 100;

	//if (Game.starts.count() > 0)
	//{
	//	pos = Game.starts.get(rand() % Game.starts.count())->getpos();
	//	pos.x-=16;
	//	pos.y-=16;
	//}
	//else
	{
		setpos(96.0f,96.0f);
	}

	alive = true;
	_angle = 0;
	weapon->setangle(0);
}

void TTank::resurrect(int x, int y)
{
	health = 100;
	arm = 100;

	setpos(x,y);

	alive = true;
	_angle = 0;
	weapon->setangle(0);
}

void TTank::setmov(unsigned char mov)
{
	movement = mov;
}

void TTank::setsteer(unsigned char steer)
{
	steering = steer;
}

float TTank::getspeed()
{
	return speed();
}

float TTank::getangle()
{
	return angle();
}

void TTank::enable()
{
	_enabled = true;
	resurrect();
}

bool TTank::enabled()
{
	return _enabled;
}

bool TTank::was_killed()
{
	if (killed)
	{
		killed = false;
		return true;
	}
}

bool TTank::is_alive()
{
	return alive;
}

void TTank::step()
{
	//if (!_enabled) return;
	if (!alive)
	{
		killtime++;
		if (killtime == 500)
		{
			resurrect();
		}
		return;
	}
	if (health <= 0)
	{
		kill();
		return;
	}

	float oldspeed = _speed;
	//куда едем?
	switch (movement)
	{
	case 0:
		if (_speed > 0.1) _speed-=0.1;
		if (_speed < -0.1) _speed+=0.1;
		if (fabs(_speed) < 0.1) _speed = 0;
		break;
	case 1:
		if (_speed < -0.1) _speed+=0.1;
		else _speed = min(_speed+0.05,3.0);
		break;
	case 2:
		if (_speed > 0.1) _speed-=0.1;
		_speed = max(_speed-0.02,-1.0);
		break;
	}

	switch (steering)
	{
	case 0:
		if (_rot_speed > 0.1) _rot_speed -= 0.1;
		if (_rot_speed < -0.1) _rot_speed += 0.1;
		if (fabs(_rot_speed) <= 0.1) _rot_speed = 0;
		break;
	case 1:
		if (_rot_speed > 0.05) _rot_speed -= 0.05;
		else _rot_speed = max(_rot_speed-0.02,-1.0);
		break;
	case 2:
		if (_rot_speed < -0.05) _rot_speed += 0.05;
		else _rot_speed = min(_rot_speed+0.02,1.0);
		break;
	}

	process();

	//перемещаем пушку и крутим ее...
	weapon->setangle(weapon->getangle()+_rot_speed);
	weapon->setpos(point(_pos.x + 10*Sin(_angle), _pos.y - 10*Cos(_angle)));
	weapon->step();

	//следы
	Tpoint tracpoint = point(_pos.x + 27*Cos(_angle), _pos.y + 27*Sin(_angle));
	if (DistanceBetweenPoints(tracpoint,last_trac1) >= 15)
	{
		Tdecal *trac = new Tdecal(tracpoint,_angle,1);
		last_trac1 = tracpoint;
		MAP.decals.push_back(trac);
	}

	tracpoint = point(_pos.x - 27*Cos(_angle), _pos.y - 27*Sin(_angle));
	if (DistanceBetweenPoints(tracpoint,last_trac2) >= 15)
	{
		Tdecal *trac = new Tdecal(tracpoint,_angle,1);
		last_trac2 = tracpoint;
		MAP.decals.push_back(trac);
	}
}

void TTank::collide(TRigidBodyStatic* coll)
{
	//printf("collide with %.2f:%.2f\n",coll->pos().x,coll->pos().y);
	//coll->destroy();
	//printf()
	if (coll->gettype() == oTypeBullet)
	{
		return;
		if (((TBullet*)coll)->pid() == 1)
		{
			return;
		}
	}
	prev_pos();
	_speed = 0;
	_rot_speed = 0;
}

bool TTank::draw()
{
	if (alive)
	{
		render.draw(sprite, _pos, box(128,128), _angle, _height);
		render.draw(wpn_sprite, weapon->getpos(), box(128,128), weapon->getangle(), 6);

		//render.draw_light(light_omni,_pos,box(96,96),0,color(1.0f,1.0f,1.0f,0.3f));
		render.draw_light(sprite,_pos,box(64,64),_angle,color(1.0f,1.0f,1.0f,0.05f));
		render.draw_light(wpn_sprite,weapon->getpos(),box(64,64),weapon->getangle(),color(1.0f,1.0f,1.0f,0.05f));
		//draw_texture(sprite,_pos,_angle);
		//draw_texture(wpn_sprite,weapon->getpos(),weapon->getangle());
		if (_light)
		{
			Tpoint left, right;
			left = point(_pos.x- 30*Sin(_angle)- 16*Cos(_angle),_pos.y+30*Cos(_angle)-16*Sin(_angle));
			render.draw_light(light_spot,left,box(192,256),_angle,color(1.0f,1.0f,1.0f,0.3f));
			right = point(_pos.x- 30*Sin(_angle)+ 16*Cos(_angle),_pos.y+30*Cos(_angle)+16*Sin(_angle));
			render.draw_light(light_spot,right,box(192,256),_angle,color(1.0f,1.0f,1.0f,0.3f));
			//render.draw_light(light_spot,_pos,box(96,128),_anlge,color(1.0f,1.0f,1.0f,0.3f));
		}
	}

	return true;
}

void TTank::setwpnangle(float dir)
{
	weapon->setpotangle(dir);
}

void TTank::setwpnrot(unsigned char rot)
{
	weapon->setrotation(rot);
}

void TTank::set_light(bool en)
{
	_light = en;
}

void TTank::shot()
{
	if (alive)
		weapon->shot();
}

void TTank::destroy()
{
	
}
