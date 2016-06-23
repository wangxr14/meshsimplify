#ifndef EDGE_H
#define EDGE_H
#include "vertex.h"
class Edge
{
	double cost;
public:
	int u, v;//point id
	bool existance;

	int position;//记录在堆中的位置
	Edge();
	Edge(int, int);
	void set_order();
	void operator=(const Edge& other);
	double getCost() const;//获取边优先级
	void setCost(double);//设置边优先级
	friend bool operator<(const Edge&, const Edge&);
	friend bool operator==(const Edge&, const Edge&);
};

#endif