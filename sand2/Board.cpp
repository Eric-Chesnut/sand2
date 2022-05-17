#include "Board.h"
#include "Pixel.h"
#include <algorithm>
#include <vector> 

Board::Board(int w, int h)
{
	if (w <= 0 || h <= 0)
	{
		//throw an error
	}
	int size = w + w * h + 1;
	positions = new int[size];
	width = w;
	height = h;
	emptyBoard();
	//setBorder(); // give it a border
}
Board::~Board()
{
	delete[] positions;
}
Board::Board(const Board& b1)
{
	int size = b1.width + b1.width * b1.height + 1;
	positions = new int[size];
	positions = b1.positions;
	width = b1.width;
	height = b1.height;
}
Board& Board::operator=(Board temp)
{
	std::swap(height, temp.height);
	std::swap(width, temp.width);
	std::swap(positions, temp.positions);
	return *this;
}
void Board::emptyBoard()
{
	
	int size = width + width * height;

	for (int p = 0; p < size; p++)
	{
		positions[p] = 0;
	}
}
int Board::getPosition(int x, int y)
{
	if (x >= 0 && x <= width && y >= 0 && y <= height)
	{
		return positions[x + y * width];
	}
	return positions[0];
}
void Board::setPosition(int x, int y, int p)
{
	if (x >= 0 && x <= width && y >= 0 && y <= height)
	{
		positions[x + y * width] = p;
	}
}
void Board::setBorder()
{
	for (int y = 0; y <= height; y++)
	{
		setPosition(0, y, -1);
		setPosition(1, y, -1);
		setPosition(width, y, -1);
		setPosition(width-1, y, -1);
	}
	for (int x = 0; x <= width; x++)
	{
		setPosition(x, 0, -1);
		setPosition(x, 1, -1);
		setPosition(x, height, -1);
		setPosition(x, height-1, -1);
	}
}
void Board::runSim()
{
	int direction;
	int size = width + width * height + 1;
	int* temp = new int[size];
	
	for (int p = 0; p < size; p++) // copy old array into temp array
	{
		temp[p] = positions[p];
	}
	emptyBoard(); // empty old array
	setBorder(); // give it a border
	for (int y = height - 2; y > 1; y--)
	{
		for (int x = 2; x < width - 1; x++)
		{
			if (temp[x + y * width] == 1) // if sand
			{
				positions[x + y * width] = temp[x + y * width]; // put the sand back where it was, then move it if it should move
				direction = rand() % 2;
				if (direction == 0)
				{
					direction = -1;
				} // checks if the thing below x, y has a lower mass then itself, and isn't a border spot
				if (temp[x + (y + 1) * width] == 0)
				{ // check again
					if (getPosition(x, y + 1) == 0)
					{
						std::swap(positions[x + y * width], positions[x + (y + 1) * width]);
						continue;
					}
				} // now checks the first diagonal, down to the right or left, down to the -direction
				if (temp[(x-direction) + (y + 1) * width]== 0)
				{
					if (getPosition(x - direction, y + 1) == 0)
					{
						std::swap(positions[x + y * width], positions[(x-direction) + (y + 1) * width]);
						continue;
					}
				}
				if (temp[(x + direction) + (y + 1) * width]== 0)
				{
					if (getPosition(x + direction, y + 1) == 0)
					{
						std::swap(positions[x + y * width], positions[(x + direction) + (y + 1) * width]);
						continue;
					}
				}
				/*
				if (temp[x + y * width].flows()) // if the pixel flows
				{ // check if -direction is empty, if so flow into it
					if (temp[(x - direction) + y * width].getMass() == 0)
					{
						if (getPosition(x - direction, y).getMass() == 0)
						{
							std::swap(positions[x + y * width], positions[(x - direction) + y * width]);
							continue;
						}
					} // other direction
					if (temp[(x + direction) + y * width].getMass() == 0)
					{
						if (getPosition(x + direction, y).getMass() == 0)
						{
							std::swap(positions[x + y * width], positions[(x + direction) + y * width]);
							continue;
						}
					}
				}*/
			}
		}
	}
	delete[] temp;
}