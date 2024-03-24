#include <fstream>
#include <string>
#include <iomanip>
#include "labirint.h"

std::vector<Cell> offset{ {-1, 0}, { 0, 1 }, { 1, 0 }, { 0, -1 } };

Labirint::Labirint(std::string fileName)
{
	this->path = std::vector<Cell>();
	this->isFinish = false;

	std::fstream file;
	file.open(fileName, std::ios::in);

	int row{};
	while (!file.eof())
	{
		std::string buffer(1024, '\0');

		file.getline(buffer.data(), buffer.length());
		
		std::vector<Cell> line;

		int column{};
		while (buffer[column])
		{
			int state;
			switch (buffer[column])
			{
			case '#': state = CellType::Wall; break;
			case ' ': state = CellType::Empty; break;
			case 's': 
			case 'S': 
				state = CellType::Start; 
				start = Cell(row, column);
				break;
			case 'f':
			case 'F':
				state = CellType::Finish;
				finish = Cell(row, column);
				break;
			default:
				break;
			}
			line.push_back(Cell(row, column, state));
			column++;
		}
	}
	file.close();
}

bool Labirint::CreateWave()
{
	std::vector<Cell> fronts[2];
	bool indexCurrent{};
	int numberFront{};

	fronts[indexCurrent].push_back(start);
	isFinish = false;

	while (true)
	{
		fronts[!indexCurrent].clear();
		numberFront++;
		for (auto cell : fronts[indexCurrent])
		{
			int row = cell.Row();
			int column = cell.Column();

			for (int i{}; i < offset.size(); i++)
			{
				int orow = row + offset[i].Row();
				int ocolumn = column + offset[i].Column();

				if (map[orow][ocolumn].State() == CellType::Finish)
				{
					map[orow][ocolumn].State() == numberFront;
					isFinish = true;
					break;
				}

				if (map[orow][ocolumn].State() == CellType::Empty)
				{
					map[orow][ocolumn].State() = numberFront;
					fronts[!indexCurrent].push_back(Cell(orow, ocolumn));
				}
			}
			if (isFinish) break;
		}
		if (isFinish) break;
		if (!fronts[!indexCurrent].size())
			break;
		indexCurrent = !indexCurrent;
	}

	return isFinish;
}

void Labirint::CreatePath()
{
	if (!isFinish) return;

	path.clear();
	path.push_back(finish);

	int row{ finish.Row() };
	int column{ finish.Column() };
	int numberFront = map[row][column].State();

	while (numberFront)
	{
		for (int i{}; i < offset.size(); i++)
		{
			row = path.back().Row();
			column = path.back().Column();

			int orow = row + offset[i].Row();
			int ocolumn = column + offset[i].Column();

			if (map[orow][ocolumn].State() == numberFront - 1)
			{
				path.push_back(Cell(orow, ocolumn));
				break;
			}
		}
		numberFront--;
	}
}
