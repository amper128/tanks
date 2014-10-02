#pragma once

#include "rigid_body_dynamic.h"
#include "../graphics/tga.h"
#include "../graphics/graphics.h"

#define tank_mov_forward = 1
#define tank_mov_backward = 2
#define tank_mov_none = 0

#include "projectile_bullet.h"
#include "projectile_fire.h"

//-------------------------------------------------------------------------
//Класс для пушки
//-------------------------------------------------------------------------
class TWeapon
{
public:
	TWeapon();
	TWeapon(char pid);

	void setpos(Tpoint p);
	void setangle(float angle);
	void setpotangle(float angle);
	void setrotation(unsigned char rot);

	Tpoint getpos();
	float getangle();

	void step();
	void shot();
	bool canshot();

	void draw();

	~TWeapon();

private:
	Tpoint pos;
	float cur_angle, pot_angle;

	float mass; //масса орудия, зависит от типа

	bool can_shot;
	int shot_timer;

	char player_id;
	float width, length;

	unsigned char rotation;
	float rotation_speed;
};

TWeapon::TWeapon()
{
	player_id = 0;
	can_shot = false;
	//_height = 6;
}

TWeapon::TWeapon(char pid)
{
	player_id = pid;
}

//-------------------------------------------------------------------------
//Класс для танка
//-------------------------------------------------------------------------
class TTank : public TRigidBodyDynamic
{
public:
	TTank();
	TTank(unsigned char pid, unsigned char typ);

//	void setpos(Tpoint p);
//	void setspeed(float sp);

	void setwpnangle(float dir);
	void setwpnrot(unsigned char rot);

//	Tpoint getpos();
//	Tpoint fut_pos();

	float getspeed();
	float getangle();

	void setmov(unsigned char mov);
	void setsteer(unsigned char steer);

	void step();
	void shot();

	void kill();
	bool was_killed();
	void resurrect();
	void resurrect(int x, int y);
	bool is_alive();

	void set_light(bool en);
	bool light() { return _light; };

	void enable();
	bool enabled();

	void collide(TRigidBodyStatic* coll);

	bool draw();

	void destroy();
	~TTank();

private:
	char player_id;
	bool _enabled;
	bool alive;
	bool killed;

	bool _light;

	float rotation_speed;

	short health,arm;

	int killtime;

	unsigned char movement; //направление движения
	unsigned char steering; //поворачивание

	Tpoint last_trac1, last_trac2;

	TWeapon *weapon;

	Sprite *wpn_sprite;
};

TTank::TTank(unsigned char pid, unsigned char typ)
{
	TTank();
}

TTank::TTank()
{
	_height = 4;
	_type = oTypeTank;
	//_type = 100;
	killtime = 0;
	alive = false;
	//mass = 2000; //2тонны О.о

	health = 100;
	arm = 100;

	weapon = new TWeapon (player_id);

	setspeed(0);
	angle(0);
	weapon->setangle(0);
	last_trac1 = last_trac2 = point(0,0);

	_bounds.w = 18*4;
	_bounds.h = 25*4;

	std::string str;

	str = "tanks/tank1.tga";
	sprite = TexManager.load(str,point(0,0));

	str = "tanks/turrel1.tga";
	wpn_sprite = TexManager.load(str,point(0,27));
	_light = false;
}

TTank::~TTank()
{
	//delete(body);
	//printf("tank destroyed\r\n");
}
