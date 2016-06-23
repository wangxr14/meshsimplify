#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include"Edge.h"
using namespace std;

struct node
{
	int position;
	double cost;
};

class Heap
{
public:
	Heap() { 
		nodes.clear();
	}
	~Heap() { }

	vector<node> nodes;

	void insert(double, int);
	void remove(int);
	void swap(int, int);//交换两个节点
	void go_up(int);//上滤
	void go_down(int);//下滤

	vector<Edge>* edgeList;
};


#endif