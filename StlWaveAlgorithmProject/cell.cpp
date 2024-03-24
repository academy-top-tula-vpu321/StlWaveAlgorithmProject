#include "cell.h"

Cell::Cell() : row{}, column{}, state{ CellType::Empty } {}

Cell::Cell(int row, int column, int state)
	: row{ row }, column{ column }, state{ state } {}

int& Cell::Row()
{
	return row;
}

int& Cell::Column()
{
	return column;
}

int& Cell::State()
{
	return state;
}

std::ostream& operator<<(std::ostream& out, const Cell& cell)
{
	out << "[" << cell.row << "," << cell.column << "]";
	return out;
}
