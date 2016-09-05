#pragma once

#include <game/IObject2D.h>

enum weapon_rotation {
	rotation_none,
	rotation_left,
	rotation_right,
};

class IBaseWeapon : public IObject2D
{
public:
	IBaseWeapon() {}
	IBaseWeapon(uint8_t pid) {}

	void rotation(enum weapon_rotation rot) { this->_rotation = rot; }

	void aim(float angle) { this->aim_angle = angle; }
	float aim(void) { return this->aim_angle; }

	virtual void step(void) = 0;
	virtual void shot(void) = 0;

	bool canshot(void) { return this->_can_shot; }

	IObjectBase * clone(void) { return NULL; }

	~IBaseWeapon() {}

protected:
	float aim_angle;

	float mass; //масса орудия, зависит от типа

	bool _can_shot;
	int _charge_timer;

	uint8_t player_id;
	float width, length;

	enum weapon_rotation _rotation;
	float rotation_speed;

private:

};
