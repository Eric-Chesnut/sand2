#pragma once
#include "Pixel.h"

class Board {
	int width, height;
	int* positions;
public:
	Board(int w, int h);
	~Board();
	Board(const Board& b1);
	Board& operator=(Board temp);
	void emptyBoard();
	int getPosition(int x, int y);
	int getPosition(int i);
	void setPosition(int x, int y, int p);
	void setBorder();
	void runSim();
};