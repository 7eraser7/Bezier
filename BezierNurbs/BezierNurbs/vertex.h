#ifndef VERTEX
#define VERTEX

class vertex
{
public:
	int x;
	int y;

	vertex();
	vertex(int _x, int _y);
	vertex(const vertex & v);
	~vertex();
	vertex & operator=(const vertex & v);
};

#endif