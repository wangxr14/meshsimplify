#include"Vector3.h"

Vector3 operator - (const Vector3& A)//È¡·´
{
	return Vector3(-A.x, -A.y, -A.z);
}

Vector3 operator + (const Vector3& A, const Vector3& B)
{
	return Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
}

Vector3 operator - (const Vector3& A, const Vector3& B)
{
	return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);
}

Vector3 operator * (const Vector3& A, const Vector3& B)
{
	return Vector3(A.x * B.x, A.y * B.y, A.z * B.z);
}

Vector3 operator / (const Vector3& A, const Vector3& B)
{
	return Vector3(A.x / B.x, A.y / B.y, A.z / B.z);
}

Vector3 operator + (const Vector3& A, const double& d)
{
	return Vector3(A.x + d, A.y + d, A.z + d);
}

Vector3 operator - (const Vector3& A, const double& d)
{
	return Vector3(A.x - d, A.y - d, A.z - d);
}

Vector3 operator * (const Vector3& A, const double& d)
{
	return Vector3(A.x * d, A.y * d, A.z * d);
}

Vector3 operator / (const Vector3& A, const double& d)
{
	return Vector3(A.x / d, A.y / d, A.z / d);
}

double Vector3::get_module()
{
	return sqrt(x*x + y*y + z*z);
}

double Vector3::get_module_square()
{
	return x*x + y*y + z*z;
}

Vector3 Vector3::get_Cross(const Vector3 A)
{
	return Vector3(y * A.z - z * A.y, z * A.x - x * A.z, x * A.y - y * A.x);
}

double Vector3::get_inner_product(const Vector3& A)
{
	return (x*A.x + y*A.y + z*A.z);
}