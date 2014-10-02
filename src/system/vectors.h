#pragma once
#include <iostream>
#include <math.h>
#include <cstdio>

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

float Cos(float x)
{
	return cos(x*DEG_TO_RAD);
}

float Sin(float x)
{
	return sin(x*DEG_TO_RAD);
}

//структура "точка"
struct Tpoint
{
        float x;
        float y;
};

//класс для векторов
class Tvector
{
private:
	float _x;
	float _y;
	float _angle;

//пока непонятно, надо ли оно
//	float angle
public:
        Tvector();				//конструктор "пустышка"
        Tvector(float x, float y);		//конструктор с координатами
	Tvector(Tpoint point);			//конструктор из точки

        float length();				//модуль вектора
	void set_length(float len);
        Tvector get_norm();			//взятие нормали к вектору
        Tvector normalize();			//нормализация вектора

        void rotate(float angle);		//поворот вектора на угол
        void set_angle(float angle);		//взятие вектора с длиной данного и повернутого на угол angle (установка абсолютного угла)
	float get_angle();			//взятие угла вектора

	float x()	{return _x;};
	float y()	{return _y;};

	float x(float val)	{_x = val;};
	float y(float val)	{_y = val;};

	//перегрузка математических операторов
	Tvector operator+(Tvector vector);	//сложение векторов
	Tvector operator-(Tvector vector);	//"вычитание" векторов (хотя по сути они реально вычитаются)

	Tvector operator*(float value);		//умножение вектора на скаляр
	Tvector operator/(float value);		//вот какая-то непонятная операция деления, вдруг пригодится

	float operator*(Tvector vector);	//скалярное произведение
//а векторное произведение на плоскости не имеет смыла, поэтому писать его не будем

	~Tvector();				//деструктор. (с) Кэп.
};

struct Tbox
{
	float w;
	float h;
};

//структура "отрезок"
struct Tsegment
{
	Tpoint A;
	Tpoint B;
};

struct Tquad
{
	Tpoint points[4];
};

class Tpolygon
{
	int pcount;
	Tpoint * points;

public:
	Tpolygon create_polygon(int count)
	{
		Tpolygon poly;
		poly.pcount = count;
		poly.points = new Tpoint[count];
		return poly;
	}

	int get_count()
	{
		return pcount;
	}
};

Tpoint point(float x, float y)
{
	Tpoint p;
	p.x = x;
	p.y = y;
	return p;
};

Tbox box(float w, float h)
{
	Tbox b;
	b.w = w;
	b.h = h;
	return b;
};

Tsegment segment(Tpoint A, Tpoint B)
{
	Tsegment s;
	s.A = A;
	s.B = B;
	return s;
};

float DegreesBetweenPoints(Tpoint pos1, Tpoint pos2);
