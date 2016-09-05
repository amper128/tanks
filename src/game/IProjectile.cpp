#include <game/IProjectile.h>
#include <game/SCFabric.h>

uint8_t IProjectile::pid()
{
	return player_id;
}

void IProjectile::pid(uint8_t id)
{
	player_id = id;
}

void IProjectile::CreateProjectile(string type, CVector pos, float an, uint8_t pid)
{
	CFabric& fabric = CFabric::GetFabric();
	IProjectile* bullet = (IProjectile*)fabric.CreateDynamic(type, pos);

	bullet->angle(an);
	bullet->pid(pid);
}
