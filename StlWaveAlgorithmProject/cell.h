#pragma once
#include <iostream>

enum CellType
{
	Empty  = -1,
	Wall   = -3,
	Start  = 0,
	Finish = -2
};

class Cell
{
	int row;
	int column;
	int state;

public:
	Cell();
	Cell(int row, int column, int state = CellType::Empty);
	int& Row();
	int& Column();
	int& State();
	friend std::ostream& operator<<(std::ostream& out, const Cell& cell);
};

