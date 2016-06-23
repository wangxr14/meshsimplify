#ifndef SIMPLIFIER_H
#define SIMPLIFIER_H
#include<vector>
#include<map>
#include"vertex.h"
#include"Edge.h"
#include"Matrix4.h"
#include"Face.h"
#include"Heap.h"

class MeshSimplifier
{
	vector<Vertex> vertexList;
	int maxID;
	vector<Edge> edgeList;
	vector<Face> faceList;
	map<pair<int, int>, int> edges;//���������жϱ��Ƿ�����ӹ�  

	int edge_num;
	int face_num;
	Heap heap;
public:
	MeshSimplifier();
	
	void addVertex(Vertex&);
	void addEdge(int, int);
	void readin(string filename);
	void cal_edge_cost(int);//���i���ߵ�costֵ
	double cal_vQ(Vector4,Vector4);
	void cal_Q(int);

	void shrink();//����
	void output(string);
	void run(double alpha);
};
#endif