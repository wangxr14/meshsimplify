#ifndef VERTEX_H
#define VERTEX_H
#include <vector>
#include <map>
#include "Vector3.h"
#include "Matrix4.h"
using namespace std;
class Vertex
{
	int id;//�ö����id
public:
	Vector3 coord;//����
	vector<int> adjacent_face;//����������ڵ���
	map<int, int> ad_edge;//key�Ǳߵ�ID��value����һ�����ID

	Vertex();
	Vertex(Vector3);
	Vertex(double, double, double);
	~Vertex();

	int getId();//��ȡid
	void setId(int);//����id

	Matrix4 Q;//ÿ�����Q����
	bool existance;
	
	friend bool operator==(const Vertex& a, const Vertex& b);//�е�
};

#endif