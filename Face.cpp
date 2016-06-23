#include "Face.h"

void Face::cal_normal_vector(Vertex a, Vertex b, Vertex c)
{
	Vector3 AB = a.coord - b.coord;
	Vector3 AC = a.coord - c.coord;
	Vector3 N = AB.get_Cross(AC);
	double m = N.get_module();
	N = N / m;
	normal_vector.value[0] = N.x;
	normal_vector.value[1] = N.y;
	normal_vector.value[2] = N.z;
	normal_vector.value[3] = -(N.x * a.coord.x + N.y * a.coord.y + N.z * a.coord.z);
}

bool Face::has_edge(const Edge& e)
{
	if ((v[0] == e.u && v[1] == e.v) || (v[0] == e.v && v[1] == e.u))
		return true;
	if ((v[0] == e.u && v[2] == e.v) || (v[0] == e.v && v[2] == e.u))
		return true;
	if ((v[2] == e.u && v[1] == e.v) || (v[2] == e.v && v[1] == e.u))
		return true;
	return false;
}