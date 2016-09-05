#include <system/vectors.h>

CPoint point(float x, float y, float z)
{
	CPoint p;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}

CPoint random_point(float max_x, float max_y, float max_z)
{
	CPoint p;
	p.x = frand() * max_x;
	p.y = frand() * max_y;
	p.z = frand() * max_z;
	return p;
}

CPoint noise_point(CPoint p, float noise)
{
	CPoint n;

	n = p;

	n.x += (frand() - 0.5f) * noise;
	n.y += (frand() - 0.5f) * noise;
	n.z += (frand() - 0.5f) * noise;

	return n;
}

CVector noise_point(CVector p, float noise)
{
	CVector n;

	n = p;

	n.x += (frand() - 0.5f) * noise;
	n.y += (frand() - 0.5f) * noise;
	n.z += (frand() - 0.5f) * noise;

	return n;
}

/*Tbox box(float w, float h)
{
	Tbox b;
	b.w = w;
	b.h = h;
	return b;
};*/

CSegment segment(CPoint A, CPoint B)
{
	CSegment s;
	s.A = A;
	s.B = B;
	return s;
}

bool IsLinesCross(CPoint p1_1, CPoint p1_2, CPoint p2_1, CPoint p2_2)
{
	float zn = (p2_2.y-p2_1.y)*(p1_2.x-p1_1.x) - (p2_2.x-p2_1.x)*(p1_2.y-p1_1.y);
	float ch1 = (p2_2.x-p2_1.x)*(p1_1.y-p2_1.y) - (p2_2.y-p2_1.y)*(p1_1.x-p2_1.x);
	float ch2 = (p1_2.x-p1_1.x)*(p1_1.y-p2_1.y) - (p1_2.y-p1_1.y)*(p1_1.x-p2_1.x);

	if (zn == 0) return false;

	if ((ch1/zn <= 1 && ch1/zn >= 0) && (ch2/zn <= 1 && ch2/zn >= 0))
		return true;
	return false;
}

bool colliderectA(CPoint p1, CBox b1, float angle1, CPoint p2, CBox b2, float angle2)
{
	CQuad q1, q2;
	int i, j;

	float cos1 = Cos(angle1), cos2 = Cos(angle2);
	float sin1 = Sin(angle1), sin2 = Sin(angle2);

	b1.w /= 2;
	b2.w /= 2;

	b1.h /= 2;
	b2.h /= 2;

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

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (IsLinesCross(q1.points[i], q1.points[((i+1) % 4)], q2.points[j], q2.points[((j+1) % 4)]))
				return true;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (IsLinesCross(q1.points[i], q1.points[((i+2) % 4)], q2.points[j], q2.points[((j+1) % 4)]))
				return true;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (IsLinesCross(q1.points[i], q1.points[((i+1) % 4)], q2.points[j], q2.points[((j+2) % 4)]))
				return true;
	return false;
}

float DegreesBetweenPoints(float X1, float Y1, float X2, float Y2)
{
	return atan2f(X2 - X1,-(Y2 - Y1)) * RAD_TO_DEG;
}

float DegreesBetweenPoints(CPoint pos1, CPoint pos2)
{
	return atan2f(-(pos2.x - pos1.x),(pos2.y - pos1.y)) * RAD_TO_DEG;
}

float DistanceBetweenPoints(CPoint p1, CPoint p2)
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

float DistanceBetweenPoints(CVector p1, CVector p2)
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

float frand()
{
	return (float)rand()/RAND_MAX;
}

float Cos(float x)
{
	return cos(x*DEG_TO_RAD);
}

float Sin(float x)
{
	return sin(x*DEG_TO_RAD);
}


//========================================
//
//	Векторная математика
//
//========================================

CVector::CVector(float nx, float ny, float nz)
{
	x = nx;
	y = ny;
	z = nz;
}

float CVector::len()
{
	return sqrt(x * x + y * y + z * z);
}

float CVector::dir()
{
	return atan2(x, y) * RAD_TO_DEG;
}

CPoint CVector::to_point()
{
	return point(x, y, z);
}

CVector CVector::operator+(const CVector& vec)
{
	return CVector(x + vec.x, y + vec.y, z + vec.z);
}

CVector CVector::operator-(const CVector& vec)
{
	return CVector(x - vec.x, y - vec.y, z - vec.z);
}

CVector CVector::operator+(const CPoint& p)
{
	return CVector(x + p.x, y + p.y, z + p.z);
}

CVector CVector::operator-(const CPoint& p)
{
	return CVector(x - p.x, y - p.y, z - p.z);
}

CVector CVector::operator*(float val)
{
	return CVector(x * val, y * val, z * val);
}

CVector CVector::operator/(float val)
{
	return CVector(x / val, y / val, z / val);
}

CVector CVector::operator=(const CPoint& p)
{
	return CVector(p.x, p.y, p.z);
}

CVector& CVector::operator+=(const CVector& vec)
{
	x += vec.x;
	y += vec.y;
	//z += vec.z;

	return *this;
}

CVector& CVector::operator-=(const CVector& vec)
{
	x -= vec.x;
	y -= vec.y;
	//z -= vec.z;

	return *this;
}

CVector& CVector::operator+=(const CPoint& p)
{
	x += p.x;
	y += p.y;
	//z += p.z;

	return *this;
}

CVector& CVector::operator-=(const CPoint& p)
{
	x -= p.x;
	y -= p.y;
	//z -= p.z;

	return *this;
}

CVector& CVector::operator*=(float val)
{
	x *= val;
	y *= val;
	//z *= val;

	return *this;
}

CVector& CVector::operator/=(float val)
{
	x /= val;
	y /= val;
	//z /= val;

	return *this;
}

bool CVector::operator==(const CVector& vec)
{
	return x == vec.x && y == vec.y && z == vec.z;
}

CVector::~CVector()
{

}

///
///    полигоны
///
///

CPoly::CPoly()
{
	vertex_count = 0;
	vertex_arr = new CPoint[vertex_count];
	vertex_arr_t = new CPoint[vertex_count];
	radius = 0;
}

CPoly::CPoly(CPoint pos)
{
	vertex_count = 0;
	vertex_arr = new CPoint[vertex_count];
	vertex_arr_t = new CPoint[vertex_count];
	radius = 0;
	_pos.x = pos.x;
	_pos.y = pos.y;
	_pos.z = pos.z;
}

void CPoly::AddVertex(float x, float y)
{
	CPoint* tmp_arr = new CPoint[vertex_count+1];
	for (uint8_t i = 0; i < vertex_count; i++) {
		tmp_arr[i] = vertex_arr[i];
	}
	delete vertex_arr;
	delete vertex_arr_t;

	vertex_arr = tmp_arr;
	vertex_count++;

	vertex_arr[vertex_count] = point(x,y);
	vertex_arr_t = new CPoint[vertex_count];

	if (sqrt(x*x + y*y) > radius)
		radius = sqrt(x*x + y*y);
}

void CPoly::rotate(float angle)
{
	float x;
	float y;

	_angle = angle;

	for (uint8_t i = 0; i < vertex_count; i++) {
		x = vertex_arr[i].x;
		y = vertex_arr[i].y;
		vertex_arr_t[i].x = x * Cos(angle) + y * Sin(angle) + _pos.x;
		vertex_arr_t[i].y = x * Sin(angle) - y * Cos(angle) + _pos.y;
	}
}

void CPoly::move(CVector pos)
{
	float dx, dy;

	dx = _pos.x - pos.x;
	dy = _pos.y - pos.y;
	_pos = pos;

	for (uint8_t i = 0; i < vertex_count; i++) {
		vertex_arr_t[i].x += dx;
		vertex_arr_t[i].y += dy;
	}
}

CVector CPoly::pos()
{
	return _pos;
}

float CPoly::angle()
{
	return _angle;
}

CPoly::~CPoly()
{
	delete vertex_arr;
	delete vertex_arr_t;
}
