#pragma once

#include "vectors.h"

Tvector::Tvector()
{
	_x = 0;
	_y = 0;
}

Tvector::Tvector(float x, float y)
{
	_x = x;
	_y = y;
}

Tvector::Tvector(Tpoint point)
{
	_x = point.x;
	_y = point.y;
}

float Tvector::length()
{
	return sqrt(_x*_x + _y*_y);
}

void Tvector::set_length(float len)
{
	float l = sqrt(_x*_x + _y*_y);
	if (l != 0)
	{
		printf("%.2f\n",len);
		Tvector tmp = get_norm()*len;
		//printf("%.2f, %.2f\n",tmp.x(),tmp.y());
		_x = tmp.x();
		_y = tmp.y();
		//printf("%.2f, %.2f\n",_x,_y);
	}
	else
	{
		_x = len*cos(_angle*DEG_TO_RAD);
		_y = len*sin(_angle*DEG_TO_RAD);
	}
}

Tvector Tvector::get_norm()
{
	float len = sqrt(_x*_x + _y*_y);
	if (len != 0)
	{
		float inv_length = 1.0f / len;
		return (*this * inv_length);
	}
	return (*this * 0);
}

Tvector Tvector::normalize()
{
	float len = sqrt(_x*_x + _y*_y);
	if (len != 0)
	{
		Tvector vect(_x/len,_y/len);
		return vect;
	}
	return (*this * 0);
}

float Tvector::get_angle()
{
	return _angle;
}

void Tvector::set_angle(float angle)
{
	_angle = angle;
	float len = sqrt(_x*_x + _y*_y);
	_x = len*cos(_angle*DEG_TO_RAD);
	_y = len*sin(_angle*DEG_TO_RAD);
}

Tvector Tvector::operator+(Tvector vect)
{
	Tvector v(_x+vect.x(), _y+vect.y());
	return v;
};

Tvector Tvector::operator-(Tvector vect)
{
	Tvector v(_x-vect.x(), _y-vect.y());
	return v;
};

Tvector Tvector::operator*(float value)
{
	Tvector vect(_x*value, _y*value);
	return vect;
};

Tvector Tvector::operator/(float value)
{
	if (value > 0)
	{
		Tvector vect(_x/value, _y/value);
		return vect;
	}
	//а что делать если все же 0?
};

float Tvector::operator*(Tvector vect)
{
	return _x*vect.x() + _y*vect.y();
}

Tvector::~Tvector()
{

}

bool IsLinesCross(Tsegment s1, Tsegment s2)
{
	float zn = (s2.B.y-s2.A.y)*(s1.B.x-s1.A.x) - (s2.B.x-s2.A.x)*(s1.B.y-s1.A.y);
	float ch1 = (s2.B.x-s2.A.x)*(s1.A.y-s2.A.y) - (s2.B.y-s2.A.y)*(s1.A.x-s2.A.x);
	float ch2 = (s1.B.x-s1.A.x)*(s1.A.y-s2.A.y) - (s1.B.y-s1.A.y)*(s1.A.x-s2.A.x);

	if (zn == 0) return false;

	if ((ch1/zn <= 1 && ch1/zn >= 0) && (ch2/zn <= 1 && ch2/zn >= 0))
		return true;
	return false;
}

//TODO: оптимизировать тут надо бы
bool colliderectA(Tpoint p1, Tbox b1, float angle1, Tpoint p2, Tbox b2, float angle2)
{
	float cos1 = Cos(angle1), cos2 = Cos(angle2);
	float sin1 = Sin(angle1), sin2 = Sin(angle2);

	b1.w /= 2;
	b2.w /= 2;

	b1.h /= 2;
	b2.h /= 2;

	Tquad q1,q2;

	//первый прямоугольник
	q1.points[0] = point(b1.w*cos1+b1.h*sin1 + p1.x,b1.w*sin1-b1.h*cos1 + p1.y);
	q1.points[1] = point(b1.w*cos1-b1.h*sin1 + p1.x,b1.w*sin1+b1.h*cos1 + p1.y);
	q1.points[2] = point(-b1.w*cos1-b1.h*sin1 + p1.x,-b1.w*sin1+b1.h*cos1 + p1.y);
	q1.points[3] = point(-b1.w*cos1+b1.h*sin1 + p1.x,-b1.w*sin1-b1.h*cos1 + p1.y);

	//второй прямоугольник
	q2.points[0] = point(b2.w*cos2+b2.h*sin2 + p2.x,b2.w*sin2-b2.h*cos2 + p2.y);
	q2.points[1] = point(b2.w*cos2-b2.h*sin2 + p2.x,b2.w*sin2+b2.h*cos2 + p2.y);
	q2.points[2] = point(-b2.w*cos2-b2.h*sin2 + p2.x,-b2.w*sin2+b2.h*cos2 + p2.y);
	q2.points[3] = point(-b2.w*cos2+b2.h*sin2 + p2.x,-b2.w*sin2-b2.h*cos2 + p2.y);

	char i,j;
	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			if (IsLinesCross(segment(q1.points[i],q1.points[((i+1) % 4)]),segment(q2.points[j],q2.points[((j+1) % 4)]))) return true;

	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			if (IsLinesCross(segment(q1.points[i],q1.points[((i+2) % 4)]),segment(q2.points[j],q2.points[((j+1) % 4)]))) return true;

	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			if (IsLinesCross(segment(q1.points[i],q1.points[((i+1) % 4)]),segment(q2.points[j],q2.points[((j+2) % 4)]))) return true;
	return false;
}

float DegreesBetweenPoints(float X1, float Y1, float X2, float Y2)
{
	return atan2f(X2 - X1,-(Y2 - Y1)) * RAD_TO_DEG;
}

float DegreesBetweenPoints(Tpoint pos1, Tpoint pos2)
{
	return atan2f(-(pos2.x - pos1.x),(pos2.y - pos1.y)) * RAD_TO_DEG;
}

float DistanceBetweenPoints(Tpoint p1, Tpoint p2)
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}
