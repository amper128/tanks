#include <game/effects.h>

TExplo::TExplo(CVector p, uint8_t /* dmg */, uint8_t /* id */)
{
	TextureManager& TexManager = TextureManager::GetInstance();
	std::string str = "effects/explosion_2.tga";

	this->_pos = p;
	this->_pos.z = 110.0f;

	this->sprite = TexManager.load(str, point(0,0), 4, 4);
	this->sprite->frame = 0;
	this->_size = {16, 16};

	this->cur_dmg = 80;

	this->_angle = float(rand() % 3600) / 10.0f;
	this->lightning = 0;
}

void TExplo::step(void)
{
	this->cur_dmg--;
	if (this->cur_dmg > 0) {
		this->_tmr++;

		if (this->_tmr >= 5) {
			this->sprite->frame++;
			this->_tmr = 0;
		}

		this->size({96.0f - this->cur_dmg, 96.0f - this->cur_dmg});

		if (this->sprite->frame < 5) {
			this->lightning += 0.05;
		} else {
			this->lightning -= 0.03;
		}
	} else {
		this->destroy();
	}

}

void TExplo::collide(IObjectStatic* body)
{
	body->damage(0.0f, 1.0f, 0.0f);
}

bool TExplo::draw(void)
{
	CRenderManager& render = CRenderManager::GetInstance();
	render.draw(this->sprite, this->_pos, CBox({128.0f, 128.0f}), this->_angle, 1.0f, 1);
//	render.draw_light(light_omni,_pos,box(128,128),0,colori(250,158,11,lightning*255));

	return true;
}

TExplo2::TExplo2(CVector p, uint8_t /* dmg */, uint8_t /* id */)
{
	TextureManager& TexManager = TextureManager::GetInstance();
	std::string str = "effects/explosion_1.tga";

	this->_pos = p;
	this->_pos.z = 110.0f;

	this->sprite = TexManager.load(str, point(0,0), 4, 4);
	this->sprite->frame = 0;
	this->_size = {16.0f, 16.0f};

	this->cur_dmg = 160;

	this->_angle = float(rand() % 3600) / 10.0f;
	this->lightning = 0;
}

void TExplo2::step()
{
	this->cur_dmg--;

	if (this->sprite->frame < 15 && this->cur_dmg > 0) {
		this->_tmr++;

		if (this->_tmr >= 10) {
			this->sprite->frame++;
			this->_tmr = 0;
		}
		this->_size = {160.0f - this->cur_dmg, 160.0f - this->cur_dmg};

		if (this->sprite->frame < 5) {
			this->lightning += 0.025;
		} else {
			this->lightning -= 0.015;
		}
	} else {
		this->destroy();
	}

}

void TExplo2::collide(IObjectStatic* body)
{
	body->damage(0.0f, 2.0f, 0.0f);
//	printf("oops!\n");
}

bool TExplo2::draw()
{
	CRenderManager& render = CRenderManager::GetInstance();
	render.draw(this->sprite, this->_pos, {192, 192}, this->_angle, 1.0f, 1);
//	render.draw_light(light_omni,_pos,box(192,192),0,colori(255,158,11,lightning*255));

	return true;
}
