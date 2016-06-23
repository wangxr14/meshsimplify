#ifndef EDGE_H
#define EDGE_H
#include "vertex.h"
class Edge
{
	double cost;
public:
	int u, v;//point id
	bool existance;

	int position;//��¼�ڶ��е�λ��
	Edge();
	Edge(int, int);
	void set_order();
	void operator=(const Edge& other);
	double getCost() const;//��ȡ�����ȼ�
	void setCost(double);//���ñ����ȼ�
	friend bool operator<(const Edge&, const Edge&);
	friend bool operator==(const Edge&, const Edge&);
};

#endif