#pragma once

#include <game/IObjectDynamic.h>

class IProjectile : public IObjectDynamic
{
protected:
	float arm_dmg; //бронебойность
	float expl_dmg; //взрывность
	float fire_dmg; //поджигательность

	//кто хозяин-то?
	uint8_t player_id;
public:
	uint8_t pid();
	void pid(uint8_t id);

	static void CreateProjectile(string type, CVector pos, float an, uint8_t pid);
};
