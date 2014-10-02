#include "projectile_bullet.h"
#include "effects.h"

TBullet::TBullet(Tpoint p, float angle, unsigned char type, unsigned char id)
{
	_type = oTypeBullet;
	_pos = p;
	_angle = angle;
	_speed = 15;

	std::string str;

	str = "projectiles/bullet.tga";
	sprite = TexManager.load(str,point(0,0));

	_bounds = box(16,16);

	arm_dmg = 20;
	expl_dmg = 5;
	_height = 5;
}

void TBullet::collide(TRigidBodyStatic * coll)
{
	if (coll->gettype() == oTypeTank || coll->gettype() == oTypeWater)
	{
		return;
		//if (((TBullet*)coll)->pid() == 1)
		//{
		//	return;
		//}
	}
	coll->damage(arm_dmg,expl_dmg);
//	printf("boom!\n");
	destroy();
}

void TBullet::step()
{
	process();
}

void TBullet::destroy()
{
	_destroyed = true;

	TExplo* explosion;
	explosion = new TExplo(_pos,16,1);
	MAP.dynamics.push_back(explosion);
}

unsigned char TBullet::pid()
{
	return player_id;
}

bool TBullet::draw()
{
	return false;
}
