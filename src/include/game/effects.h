#pragma once

#include <game/IObjectDynamic.h>
#include <graphics/render_manager.h>

class TExplo : public IObjectDynamic
{
public:
	TExplo(CVector pos, uint8_t dmg, uint8_t);

	void step(void);
	bool draw(void);
	void collide(IObjectStatic* body);

	std::string getClassName(void) { return "TExplo"; }
	IObjectBase* clone(void) { return new TExplo(*this); }

	~TExplo() {}

private:
	uint32_t cur_dmg;
	uint32_t cur_size;
	uint32_t _tmr;
	float lightning;
};

class TExplo2 : public IObjectDynamic
{
public:
	TExplo2(CVector pos, uint8_t, uint8_t);

	void step(void);
	bool draw(void);
	void collide(IObjectStatic* body);

	std::string getClassName(void) { return "TExplo2"; }
	IObjectBase* clone(void) { return new TExplo2(*this); }

	~TExplo2() {}

private:

	uint32_t cur_dmg;
	uint32_t cur_size;
	uint32_t _tmr;
	float lightning;
};

