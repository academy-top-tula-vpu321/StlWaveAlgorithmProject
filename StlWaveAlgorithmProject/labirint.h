#pragma once
#include "cell.h"
#include <vector>

typedef std::vector<std::vector<Cell>> Matrix;

class Labirint
{
	Matrix map;
	Cell start;
	Cell finish;
	std::vector<Cell> path;

	bool isFinish;

public:
	Labirint() {};
	Labirint(std::string fileName);

	void Print();
	bool CreateWave();
	void CreatePath();
};

