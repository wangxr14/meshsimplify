#ifndef VERTEX_H
#define VERTEX_H
#include <vector>
#include <map>
#include "Vector3.h"
#include "Matrix4.h"
using namespace std;
class Vertex
{
	int id;//该顶点的id
public:
	Vector3 coord;//坐标
	vector<int> adjacent_face;//与这个点相邻的面
	map<int, int> ad_edge;//key是边的ID，value是另一个点的ID

	Vertex();
	Vertex(Vector3);
	Vertex(double, double, double);
	~Vertex();

	int getId();//获取id
	void setId(int);//设置id

	Matrix4 Q;//每个点的Q矩阵
	bool existance;
	
	friend bool operator==(const Vertex& a, const Vertex& b);//判等
};

#endif