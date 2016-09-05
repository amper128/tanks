#include <game/projectile_bullet.h>
#include <game/effects.h>

#include <game/SCFabric.h>
#include <game/GCVehicleMiddleTank.h>

CProjectileBullet::CProjectileBullet(CVector p)
{
	std::string str;
	TextureManager& TexManager = TextureManager::GetInstance();

	_type = "CProjectile";
	solid = false;
	p.z = 5;
	pos(p);
	_speed = 15;

	str = "projectiles/bullet.tga";
	sprite = TexManager.load(str, point(0,0));

	_size = {16, 16};

	arm_dmg = 20;
	expl_dmg = 5;
}

void CProjectileBullet::collide(IObjectStatic * coll)
{
	if (!coll->solid) return;
	if (coll->flat) return;
	if (coll->gettype() == "CVehicle" && ((TTank*)coll)->pid() == player_id)
	{
		return;
	}
	coll->damage(arm_dmg,expl_dmg);

//	IObjectStatic* fabric.CreateDynamic();
/*	CFabric& fabric = CFabric::GetFabric();
	TExplo* explosion;
	explosion = (TExplo*)fabric.CreateDynamic("TExplo", _pos);*/

//	explosion = new TExplo(_pos,16,1);
	destroy();
}

void CProjectileBullet::step()
{

}

unsigned char CProjectileBullet::pid()
{
	return player_id;
}

bool CProjectileBullet::draw()
{
	return false;
}
