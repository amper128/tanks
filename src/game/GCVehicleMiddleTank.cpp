#include <game/GCVehicleMiddleTank.h>
#include <game/IProjectile.h>

TWeapon::TWeapon()
{
	player_id = 0;
	_can_shot = false;
	_pos.z = 10;
}

TWeapon::TWeapon(uint8_t pid)
{
	player_id = pid;
}

TWeapon::~TWeapon()
{

}

void TWeapon::step()
{
	switch (_rotation) {
	default:
		if (rotation_speed > 0.05) rotation_speed -= 0.05;
		if (rotation_speed < -0.05) rotation_speed += 0.05;
		if (fabs(rotation_speed) < 0.05) rotation_speed = 0;
		break;
	case rotation_left:
		if (rotation_speed < -0.05) rotation_speed += 0.05;
		else rotation_speed = min(rotation_speed+0.02,1.0);
		break;
	case rotation_right:
		if (rotation_speed > 0.05) rotation_speed -= 0.05;
		else rotation_speed = max(rotation_speed-0.02,-1.0);
		break;
	}

	_angle += rotation_speed;

	if (!_can_shot) {
		_charge_timer++;
		if (_charge_timer >= 200) {
			_can_shot = true;
			_charge_timer = 0;
		}
	}
}

void TWeapon::shot()
{
	if (_can_shot) {
		CVector np;
/*		np.x = pos.x - 60*Sin(cur_angle) - 30*Cos(cur_angle);
		np.y = pos.y + 60*Cos(cur_angle) - 30*Sin(cur_angle);
		IProjectile::CreateProjectile("CProjectileFire",np, cur_angle+frand()*10-5, player_id);

		np.x = pos.x - 60*Sin(cur_angle) + 30*Cos(cur_angle);
		np.y = pos.y + 60*Cos(cur_angle) - 30*Sin(-cur_angle);
		IProjectile::CreateProjectile("CProjectileFire",np, cur_angle+frand()*10-5, player_id);

		can_shot = false;
		shot_timer = 0;*/

		np.x = _pos.x - 60 * Sin(_angle);
		np.y = _pos.y + 60 * Cos(_angle);

		//IProjectile::CreateProjectile("CProjectileBullet", np, _angle + frand() * 1 - 0.5, player_id);

		_can_shot = false;
	}
}

TTank::TTank(uint8_t pid, uint8_t typ)
{
	TextureManager& TexManager = TextureManager::GetInstance();
	std::string str;

	player_id = pid;

	_pos.z = 4;
	_type = "CVehicle";
	killtime = 0;
	alive = false;
	//mass = 2000; //2тонны О.о

	health = 100;
	arm = 100;

	weapon = new TWeapon(pid);

	_speed = 0;
	_angle = 0;
	weapon->angle(0);
	last_trac1 = last_trac2 = point(0,0);

	size({18*4,25*4});

	str = "tanks/tank1.tga";
	sprite = TexManager.load(str,point(0,0));

	str = "tanks/turrel1.tga";
	wpn_sprite = TexManager.load(str,point(0,27));
	_light = false;

	_alpha = 0;
	killtime = 1000;
}

TTank::~TTank()
{
	//delete(body);
	//printf("tank destroyed\r\n");
}

void TTank::kill(void)
{
	TextureManager& TexManager = TextureManager::GetInstance();
	std::string str;

	if (alive) {
		//TExplo2* explosion;
		//CVector p;

		alive = false;
		killtime = 0;
		std::cout << "player was killed!\n";
		killed = true;

		_pos = noise_point(_pos, 64);
		//explosion = new TExplo2(p, 32, 1);

/*		MAP.dynamics.push_back(explosion);

		explosion = new TExplo2(_pos,32,1);
		MAP.dynamics.push_back(explosion);

		p = noise_point(_pos,96);
		explosion = new TExplo2(p,32,1);
		MAP.dynamics.push_back(explosion);

		explosion = new TExplo2(_pos,32,1);
		MAP.dynamics.push_back(explosion);

		p = noise_point(_pos,96);
		explosion = new TExplo2(p,32,1);
		MAP.dynamics.push_back(explosion);

		explosion = new TExplo2(_pos,32,1);
		MAP.dynamics.push_back(explosion);*/


		str = "tanks/tank1_dead.tga";
		sprite = TexManager.load(str,point(0,0));

		str = "tanks/turrel1_dead.tga";
		wpn_sprite = TexManager.load(str,point(0,27));
	}
}

void TTank::resurrect(void)
{
	TextureManager& TexManager = TextureManager::GetInstance();
	std::string str;

	printf("resurrect...\n");

	str = "tanks/tank1.tga";
	sprite = TexManager.load(str,point(0,0));

	str = "tanks/turrel1.tga";
	wpn_sprite = TexManager.load(str,point(0,27));

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
		_pos = CVector(96.0f, 96.0f);
	}

	alive = true;
	_angle = 0;
	_alpha = 1;
	weapon->angle(0);
	weapon->step();

	printf("resurrect finished...\n");
}

void TTank::resurrect2(CVector pos)
{
	printf("resurrect2...\n");
	health = 100;
	arm = 100;

	_pos = pos;

	alive = true;
	_angle = 0;
	weapon->angle(0);

	printf("resurrect2 finished...\n");
}

void TTank::enable()
{
	_enabled = true;
	resurrect();
}

bool TTank::enabled(void)
{
	return _enabled;
}

bool TTank::was_killed(void)
{
	if (killed) {
		killed = false;
		return true;
	}
	return false;
}

bool TTank::is_alive(void)
{
	return alive;
}

void TTank::damage(float dmg1, float dmg2, float dmg3)
{
	if (alive) {
		health -= dmg1*0.2f;
		health -= dmg2*0.02f;
		health -= dmg3*0.04f;
	}
}

void TTank::step()
{
	//if (!_enabled) return;
	if (!alive) {
		killtime++;
		if (killtime < 500) {
			_alpha = 1 - float(killtime / 500.0f);
		}
		if (killtime == 1500) {
			resurrect();
		}
		return;
	}
	if (health <= 0) {
		kill();
		return;
	}

	//куда едем?
	switch (_moving) {
	case moving_none:
		if (_speed > 0.1f) _speed -= 0.1f;
		if (_speed < -0.1f) _speed += 0.1f;
		if (fabs(_speed) < 0.1f) _speed = 0;
		break;
	case moving_forward:
		if (_speed < -0.1f) _speed += 0.1;
		else _speed = min(_speed + 0.05f, 3.0f);
		break;
	case moving_backward:
		if (_speed > 0.1f) _speed -= 0.1f;
		_speed = max(_speed - 0.02f, -1.0f);
		break;
	}

	switch (_steering) {
	case steering_none:
		if (_rot_speed > 0.1) _rot_speed -= 0.1;
		if (_rot_speed < -0.1) _rot_speed += 0.1;
		if (fabs(_rot_speed) <= 0.1) _rot_speed = 0;
		break;
	case steering_right:
		if (_rot_speed > 0.05) _rot_speed -= 0.05;
		else _rot_speed = max(_rot_speed-0.02,-1.0);
		break;
	case steering_left:
		if (_rot_speed < -0.05) _rot_speed += 0.05;
		else _rot_speed = min(_rot_speed+0.02,1.0);
		break;
	}

//	process();

	//перемещаем пушку и крутим ее...
	weapon->angle(weapon->angle()+_rot_speed);
	weapon->pos(CVector(_pos.x + 10*Sin(_angle), _pos.y - 10*Cos(_angle), 6));
	weapon->step();

/*
TODO: переписать на партиклы
	//следы
	Tpoint tracpoint = point(_pos.x + 27*Cos(_angle), _pos.y + 27*Sin(_angle));
	if (DistanceBetweenPoints(tracpoint,last_trac1) >= 15)
	{
		Tdecal *trac = new Tdecal(tracpoint,_angle,1);
		last_trac1 = tracpoint;
//		MAP.particles.push_back(trac);
	}

	tracpoint = point(_pos.x - 27*Cos(_angle), _pos.y - 27*Sin(_angle));
	if (DistanceBetweenPoints(tracpoint,last_trac2) >= 15)
	{
		Tdecal *trac = new Tdecal(tracpoint,_angle,1);
		last_trac2 = tracpoint;
//		MAP.particles.push_back(trac);
	}
*/
}

void TTank::collide(IObjectStatic* coll)
{
	if (!coll->solid)
	{
		return;
	}
	prev_pos();
	_speed = 0;
	_rot_speed = 0;
}

bool TTank::draw()
{
	CRenderManager& render = CRenderManager::GetInstance();

	if (alive) {
		render.draw(this->sprite, this->_pos, {128, 128}, this->_angle);
		render.draw(this->wpn_sprite, this->weapon->pos(), {128, 128}, this->weapon->angle());

		render.draw_light(this->sprite, this->_pos, {64,64}, this->_angle, color(1.0f, 1.0f, 1.0f, 0.05f));
		render.draw_light(this->wpn_sprite, this->weapon->pos(), {64,64}, this->weapon->angle(), color(1.0f,1.0f,1.0f,0.05f));
		if (_light) {
			CPoint left, right;
			left = point(this->_pos.x - 30 * Sin(this->_angle) - 16 * Cos(this->_angle),
				     this->_pos.y + 30 * Cos(this->_angle) - 16 * Sin(this->_angle));
			right = point(this->_pos.x - 30 * Sin(this->_angle) + 16 * Cos(this->_angle),
				      this->_pos.y + 30 * Cos(this->_angle) + 16 * Sin(this->_angle));

			//render->draw_light(light_spot,left,box(192,256),_angle,color(1.0f,1.0f,1.0f,0.3f));
			//render->draw_light(light_spot,right,box(192,256),_angle,color(1.0f,1.0f,1.0f,0.3f));
		}
	} else if (killtime < 500) {
		render.draw(this->sprite, this->_pos, {128, 128}, this->_angle, this->_alpha);
		render.draw(this->wpn_sprite, this->weapon->pos(), {128, 128}, this->weapon->angle(), this->_alpha);
	}

	return true;
}

void TTank::setwpnangle(float dir)
{
	weapon->aim(dir);
}

void TTank::setwpnrot(enum weapon_rotation rot)
{
	weapon->rotation(rot);
}

void TTank::set_light(bool en)
{
	_light = en;
}

void TTank::shot(void)
{
	if (alive) {
		weapon->shot();
	}
}

void TTank::destroy(void)
{

}
