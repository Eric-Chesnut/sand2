#include "Pixel.h"
Pixel::Pixel()
{
	mass = 0;
	flow = false;
	r = g = b = a = 255;
}

Pixel::Pixel(int m, bool f, int r1, int g1, int b1, int a1)
{
	if (m < -1 || m == 0 || r1 < 0 || r1 > 255 || g1 < 0 || g1 > 255 || b1 < 0 || b1 > 255 || a1 < 0 || a1 > 255)
	{
		//error, not allowed, error message
		mass = 0;
		flow = false;
		r = g = b = a = 255;
		return;
	}
	mass = m;
	flow = f;
	r = r1;
	g = g1;
	b = b1;
	a = a1;
}

int Pixel::getMass()
{
	return mass;
}
bool Pixel::flows()
{
	return flow;
}
int Pixel::getR()
{
	return r;
}
int Pixel::getG()
{
	return g;
}
int Pixel::getB()
{
	return b;
}
int Pixel::getA()
{
	return a;
}