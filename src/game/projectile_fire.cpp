#include <game/projectile_fire.h>
#include <game/effects.h>
#include <game/GCVehicleMiddleTank.h>

#include <system/strings.h>

static Sprite* light_omni;
//static Sprite* light_spot;

CProjectileFire::CProjectileFire(CVector p)
{
	TextureManager& TexManager = TextureManager::GetInstance();
	string str;

	this->_type = "CProjectile";
	this->solid = false;
	this->_pos = p;
	this->_pos.z = 5;
	this->_speed = 5;

	str = "projectiles/fire.tga";
	this->sprite = TexManager.load(str, point(0,0), 2, 2);
	this->_size = {20.0f, 20.0f};

	this->arm_dmg = 0.1f;
	this->expl_dmg = 0.1f;
	this->fire_dmg = 10;

	this->life_time = 120;
	this->fire_time = 200;
	this->_act = 0;
	this->tex_angle = frand() * 360.0f;


	if (!light_omni) {
		light_omni = TexManager.load("lights/round.tga", point(0,0));
	}
}

void CProjectileFire::collide(IObjectStatic * coll)
{
	if (coll->flat) {
		return;
	}

	if (_act == 0) {
		//if (coll->gettype() == "CVehicle" && ((TTank*)coll)->pid() == player_id)
		//	return;
		_act = 1;
		_speed = 0;
	}
	coll->damage(arm_dmg, expl_dmg, 0.0f);
}

void CProjectileFire::step()
{
	_tmr++;
	if (_tmr >= 10) {
		sprite->frame++;
		_tmr = 0;
	}
	if (_pos.z < 120) {
		_pos.z++;
	}
	if (_size.w < 64) {
		_size.w+=0.5;
		_size.h+=0.5;
	}
	if (_act == 0) {
		_alpha -= 0.02f;
		if (_alpha <= 0)
			destroy();
		process();
	} else if (_act == 1) {
		fire_time--;
		if (fire_time < 200) {
			_alpha -= 0.003f;
		}
		if (_alpha <= 0) {
			destroy();
		}
	}

	arm_dmg = 0.1*_alpha;
	expl_dmg = 0.1*_alpha;
	fire_dmg = 0.1*_alpha;
}

bool CProjectileFire::draw(void)
{
	CRenderManager& render = CRenderManager::GetInstance();

	render.draw(this->sprite, this->_pos, {this->_size.w * 2, this->_size.h * 2}, this->tex_angle, this->_alpha, 1);
	render.draw_light(light_omni, this->_pos, {this->_size.w * 2, this->_size.h * 2}, 0, colori(252, 148, 4, this->_alpha * 255));

	return true;
}
