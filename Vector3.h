#ifndef MYVEC3D_H
#define MYVEC3D_H

#include <cmath>
//三维向量类
class Vector3
{

public:
	Vector3(double X = 0, double Y = 0, double Z = 0) : x(X), y(Y), z(Z) {};
	~Vector3(void){};
	double x, y, z;
	friend Vector3 operator - (const Vector3&);//取反
	friend Vector3 operator + (const Vector3&, const Vector3&);
	friend Vector3 operator - (const Vector3&, const Vector3&);
	friend Vector3 operator * (const Vector3&, const Vector3&);
	friend Vector3 operator / (const Vector3&, const Vector3&);
	friend Vector3 operator + (const Vector3&, const double&);
	friend Vector3 operator - (const Vector3&, const double&);
	friend Vector3 operator * (const Vector3&, const double&);
	friend Vector3 operator / (const Vector3&, const double&);

	double get_module();
	double get_module_square();
	Vector3 get_Unit_Vector();//获得自己的单位向量
	Vector3 get_Vertical_Vector();//获得与自己垂直的单位向量
	Vector3 get_Cross(const Vector3);
	double get_inner_product(const Vector3&);
};

#endif

