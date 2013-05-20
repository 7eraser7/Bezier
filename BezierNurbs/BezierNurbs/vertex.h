#ifndef VERTEX
#define VERTEX

class vertex
{
public:
	double x;
	double y;

	vertex();
	vertex(double _x, double _y);
	vertex(const vertex & v);
	~vertex();
	vertex & operator=(const vertex & v);
};

#endif