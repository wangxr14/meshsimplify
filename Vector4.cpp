#include"Vector4.h"


Vector4::Vector4()
{
	for (int i = 0; i < 4; ++i)
		value[i] = 0;
}

Vector4::Vector4(double _x, double _y, double _z, double _w)
{
	value[0] = _x;
	value[1] = _y;
	value[2] = _z;
	value[3] = _w;
}

Vector4::~Vector4()
{

}

Vector4 operator+(const Vector4& a, const Vector4& b)
{
	Vector4 ret;
	for (int i = 0; i < 4; ++i)
		ret.value[i] = a.value[i] + b.value[i];
	return ret;
}

double Vector4::get_inner_product(const Vector4& A)
{
	double ret;
	for (int i = 0; i < 4; ++i)
		ret += value[i] * A.value[i];
	return ret;
}