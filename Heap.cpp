#include"Heap.h"

void Heap::insert(double _cost, int _pos)
{
	node tmp;
	tmp.cost = _cost;
	tmp.position = _pos;
	nodes.push_back(tmp);
	(*edgeList)[_pos].position = nodes.size() - 1;
	go_up(nodes.size() - 1);
}

void Heap::swap(int x, int y)
{
	(*edgeList)[nodes[y].position].position = x;
	(*edgeList)[nodes[x].position].position = y;

	node tmp = nodes[y];
	nodes[y] = nodes[x];
	nodes[x] = tmp;
}

void Heap::go_up(int x)
{
	while (x > 0)
	{
		int parent = (x - 1) / 2;
		if (nodes[parent].cost > nodes[x].cost)
		{
			swap(parent, x);
			x = parent;
		}
		else break;
	}
}

void Heap::remove(int x)
{
	swap(x, nodes.size() - 1);
	nodes.pop_back();
	go_down(x);
}

void Heap::go_down(int x)
{
	int lc, rc;
	while (2 * x + 1 < nodes.size())
	{
		lc = 2 * x + 1;
		rc = lc + 1;
		if (rc < nodes.size() && nodes[rc].cost < nodes[lc].cost)
			lc = rc;
		if (nodes[lc].cost < nodes[x].cost)
		{
			swap(lc, x);
			x = lc;
		}
		else break;
	}
}
