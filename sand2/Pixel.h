#pragma once
class Pixel {
	int mass;
	bool flow;
	int r, g, b, a;
public:
	Pixel();
	Pixel(int m, bool f, int r1, int g1, int b1, int a1);
	int getMass();
	bool flows();
	int getR();
	int getG();
	int getB();
	int getA();
};