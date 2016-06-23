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
	void swap(int, int);//���������ڵ�
	void go_up(int);//����
	void go_down(int);//����

	vector<Edge>* edgeList;
};


#endif