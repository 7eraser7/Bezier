#include "vertex.h"

vertex::vertex()
{
	x = 0;
	y = 0;
}

vertex::vertex(double _x, double _y)
{
	x = _x;
	y = _y;
}
vertex::vertex(const vertex & v)
{
	x = v.x;
	y = v.y;
}

vertex::~vertex()
{

}

vertex & vertex::operator=(const vertex & v)
{
	if (this == &v)
		return *this;

	x = v.x;
	y = v.y;

	return *this;
}