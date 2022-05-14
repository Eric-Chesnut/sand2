#pragma once
#include "Pixel.h"

class Board {
	int width, height;
	Pixel* positions;
public:
	Board(int w, int h);
	~Board();
	Board(const Board& b1);
	Board& operator=(Board temp);
	void emptyBoard();
	Pixel& getPosition(int x, int y);
	void setPosition(int x, int y, Pixel p);
	void setBorder();
	void runSim();
};