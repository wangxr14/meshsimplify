#include "edge.h"
#include <iostream>
#include <cmath>
using namespace std;

Edge::Edge()
{
	u = 0;
	v = 0;
	cost = 0;
	existance = true;
}

Edge::Edge(int _u, int _v) :u(_u), v(_v)
{
	cost = 0;
	existance = true;
}

void Edge::operator=(const Edge& a)
{
	u = a.u;
	v = a.v;
	cost = a.cost;
}

void Edge::setCost(double _cost)
{
	cost = _cost;
}

double Edge::getCost() const
{
	return cost;
}

void Edge::set_order()
{
	if (u > v)
	{
		int tmp = u;
		u = v;
		v = tmp;
	}
}

bool operator<(const Edge& a, const Edge& b)//重载小于
{
	return (bool)(a.getCost() > b.getCost());
}

bool operator==(const Edge& a, const Edge& b)//重载判等
{
	if ((a.u == b.u&&a.v == b.v) || (a.u == b.v && a.v == b.u)) return true;
	return false;
}
