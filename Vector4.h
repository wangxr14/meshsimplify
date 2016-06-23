#ifndef MYVEC4D_H
#define MYVEC4D_H

#include <cmath>
//四维向量类
class Vector4
{

public:
	Vector4(double, double, double, double);
	Vector4();
	~Vector4(void);
	double value[4];

	friend Vector4 operator + (const Vector4&, const Vector4&);
	double get_inner_product(const Vector4&);
};

#endif
