#ifndef MATRIX4_H
#define MATRIX4_H
#include "Vector4.h"

class Matrix4
{
public:
	double mat[4][4];
	Matrix4();
	friend Matrix4 operator+(const Matrix4&, const Matrix4&);
	void operator=(const Matrix4&);
	Matrix4 multi_k(const Vector4&);//计算每个平面对于的矩阵K
	Vector4 left_multi(const Vector4&);//计算Q*V转置
	void clear();
};

#endif