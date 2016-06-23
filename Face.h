#ifndef FACE_H
#define FACE_H
#include "vertex.h"
#include "Edge.h"
class Face
{
	
public:
	int v[3];//save vertex ID
	Vector4 normal_vector;//平面方程,a,b,c,d
	bool existance;

	Face(){
		v[0] = v[1] = v[2] = 0;
		existance = true;
	}
	Face(int a, int b, int c)
	{
		v[0] = a;
		v[1] = b;
		v[2] = c;
		existance = true;
	}
	void cal_normal_vector(Vertex a,Vertex b,Vertex c);
	bool has_edge(const Edge&);
};

#endif