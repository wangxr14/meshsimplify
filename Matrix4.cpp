#include"Matrix4.h"

Matrix4::Matrix4()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			mat[i][j] = 0.0;
}

Matrix4 operator+(const Matrix4& a, const Matrix4& b)
{
	Matrix4 ret;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			ret.mat[i][j] = a.mat[i][j] + b.mat[i][j];
	return ret;
}

void Matrix4::operator=(const Matrix4& a)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mat[i][j] = a.mat[i][j];
}

Matrix4 Matrix4::multi_k(const Vector4& p)
{
	Matrix4 k;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			k.mat[i][j] = p.value[i] * p.value[j];
	return k;
}

Vector4 Matrix4::left_multi(const Vector4& v)
{
	Vector4 ret;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ret.value[i] += this->mat[i][j] * v.value[j];
		}
	}
	return ret;
}

void Matrix4::clear()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat[i][j] = 0;
		}
	}
}