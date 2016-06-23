#include "vertex.h"

Vertex::Vertex() :coord(0, 0, 0)
{
	id = 0;
	adjacent_face.clear();
	ad_edge.clear();
	existance = true;
}

Vertex::Vertex(Vector3 _coord)
{
	coord = _coord;
	id = 0;
	adjacent_face.clear();
	ad_edge.clear();
	existance = true;
}

Vertex::Vertex(double _x, double _y, double _z) :coord(_x, _y, _z)
{
	id = 0;
	adjacent_face.clear();
	ad_edge.clear();
	existance = true;
}

Vertex::~Vertex()
{

}

int Vertex::getId()
{
	return id;
}

void Vertex::setId(int _id)
{
	id = _id;
}

bool operator==(const Vertex& a, const Vertex& b)
{
	return (bool)(a.id == b.id);
}