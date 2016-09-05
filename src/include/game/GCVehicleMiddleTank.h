#pragma once

#include <game/projectile_bullet.h>
#include <game/projectile_fire.h>
#include <game/effects.h>

#include <game/IVehicleBase.h>
#include <game/IWeaponBase.h>

//-------------------------------------------------------------------------
//Класс для пушки
//-------------------------------------------------------------------------
class TWeapon : public IBaseWeapon
{
public:
	TWeapon();
	TWeapon(uint8_t pid);

	void step(void);
	void shot(void);

	bool draw(void) { return true; }

	~TWeapon();

private:

};

//-------------------------------------------------------------------------
//Класс для танка
//-------------------------------------------------------------------------
class TTank : public IBaseVehicle
{
private:
	uint8_t player_id;
	bool _enabled;
	bool alive;
	bool killed;

	bool _light;

	float rotation_speed;

	float health,arm;

	int killtime;

	CVector last_trac1, last_trac2;

	TWeapon *weapon;

	Sprite *wpn_sprite;
public:
	TTank(uint8_t pid = 0, uint8_t typ = 1);

	void setwpnangle(float dir);
	void setwpnrot(weapon_rotation rot);

	void step(void);
	void shot(void);

	void kill(void);
	bool was_killed(void);
	void resurrect(void);
	void resurrect2(CVector pos = {0.0f, 0.0f, 0.0f});
	bool is_alive(void);
	int kill_timer(void) { return killtime; }

	uint8_t pid(void) { return player_id; }

	void set_light(bool en);
	bool light(void) { return _light; }

	void enable(void);
	bool enabled(void);

	void collide(IObjectStatic* coll);
	void damage(float dmg1, float dmg2, float dmg3);

	bool draw(void);

	std::string getClassName(void) { return "CVehicleMiddleTank"; }
	IObjectBase* clone(void) { printf("clone tank\n");return new TTank(*this); }

	void destroy(void);
	~TTank();
};
