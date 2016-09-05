#pragma once

#include <iostream>
#include <math.h>
#include <cstdio>
#include <cstdlib>

#include "sys.h"

#define RAD_TO_DEG 57.2957795130823208767981548141052
#define DEG_TO_RAD 0.0174532925199432957692369076848861

//шаблоны для Min и Max
//уже не помню почему их пришлось реализовывать самостоятельно
template <class T> const T& min ( const T& a, const T& b ) {
	return (a<b)?a:b;
}

template <class T> const T& max ( const T& a, const T& b ) {
	return (a>b)?a:b;
}

float frand();

float Cos(float x);
float Sin(float x);

//структура "точка"
typedef struct
{
	float x;
	float y;
	float z;
} CPoint;

typedef struct
{
	CPoint points[4];
} CQuad;

typedef struct
{
	CPoint A;
	CPoint B;
} CSegment;

typedef struct {
	float w;
	float h;
} CBox;

CPoint point(float x, float y, float z = 0);

class CVector
{
public:
	CVector(float nx = 0, float ny = 0, float nz = 0);

	float len();
	float dir();

	float x;
	float y;
	float z;

	CPoint to_point();

	CVector operator+(const CVector& vec);
	CVector operator-(const CVector& vec);
	CVector operator+(const CPoint& p);
	CVector operator-(const CPoint& p);
	CVector operator*(const float val);
	CVector operator/(const float val);
	CVector operator=(const CPoint& p);

	CVector& operator+=(const CVector& vec);
	CVector& operator-=(const CVector& vec);
	CVector& operator+=(const CPoint& p);
	CVector& operator-=(const CPoint& p);
	CVector& operator*=(const float val);
	CVector& operator/=(const float val);

	bool operator==(const CVector& vec);

	~CVector();
};

class CPoly
{
private:
	CPoint* vertex_arr;
	float radius;
	CVector _pos;
	float _angle;

protected:

public:
	CPoly();
	CPoly(CPoint origin);

	CPoint * vertex_arr_t;
	uint8_t vertex_count;

	void AddVertex(float x, float y);

	void rotate(float angle);
	float angle();

	void move(CVector pos);
	CVector pos();

	~CPoly();
};

CPoint random_point(float max_x, float max_y, float max_z = 0);
CPoint noise_point(CPoint p, float noise);
CVector noise_point(CVector p, float noise);

bool colliderectA(CPoint p1, CBox b1, float angle1, CPoint p2, CBox b2, float angle2);

float DistanceBetweenPoints(CPoint p1, CPoint p2);
float DistanceBetweenPoints(CVector p1, CVector p2);
float DegreesBetweenPoints(CPoint pos1, CPoint pos2);
bool IsLinesCross(CPoint p1_1, CPoint p1_2, CPoint p2_1, CPoint p2_2);
