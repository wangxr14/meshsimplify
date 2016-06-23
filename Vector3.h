#ifndef MYVEC3D_H
#define MYVEC3D_H

#include <cmath>
//��ά������
class Vector3
{

public:
	Vector3(double X = 0, double Y = 0, double Z = 0) : x(X), y(Y), z(Z) {};
	~Vector3(void){};
	double x, y, z;
	friend Vector3 operator - (const Vector3&);//ȡ��
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
	Vector3 get_Unit_Vector();//����Լ��ĵ�λ����
	Vector3 get_Vertical_Vector();//������Լ���ֱ�ĵ�λ����
	Vector3 get_Cross(const Vector3);
	double get_inner_product(const Vector3&);
};

#endif

