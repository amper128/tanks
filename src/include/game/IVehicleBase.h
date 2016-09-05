#pragma once

#include "IObjectDynamic.h"

enum vehicle_moving {
	moving_none,
	moving_forward,
	moving_backward,
};

enum vehicle_steering {
	steering_none,
	steering_left,
	steering_right,
};

class IBaseVehicle : public IObjectDynamic
{
public:
	void setmov(enum vehicle_moving mov) { _moving = mov; }
	void setsteer(enum vehicle_steering steer) { _steering = steer; }

protected:
	enum vehicle_moving _moving;
	enum vehicle_steering _steering;
};
