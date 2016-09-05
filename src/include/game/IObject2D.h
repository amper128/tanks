#pragma once

#include <system/vectors.h>
#include <graphics/graphics.h>
#include <system/resource_manager.h>
#include <graphics/render_manager.h>
#include <game/constants.h>
#include <game/IObjectBase.h>

class IObject2D : public IObjectBase
{
protected:
	CVector	_pos;
	float	_angle;
	bool	_destroyed;
	float	_alpha;
	CBox	_size;

public:
	Sprite* sprite;

	IObject2D();

	CVector	pos();
	float	angle();
	CBox	size();
	float	alpha();

	void	size(CBox s);
	void	angle(float a);
	void	pos(CVector p);
	void	alpha(float a);

	virtual	bool draw(void) { return false; }
	virtual	void process(void) {}

	virtual void destroy(void) { _destroyed = true; }
	virtual	bool destroyed(void) { return _destroyed; }

	virtual ~IObject2D();
};
