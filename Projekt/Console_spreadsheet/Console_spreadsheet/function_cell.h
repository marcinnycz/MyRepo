#pragma once
#include "cell.h"

#define MAX_ROWS 512
#define MAX_COLUMNS 128

class FunctionCell : public Cell
{
	std::string result;
	Cell* (*table)[MAX_ROWS][MAX_COLUMNS];
	double sum(int fcolumn, int frow, int lcolumn, int lrow);
	double sum(std::string list);
	double max(int fcolumn, int frow, int lcolumn, int lrow);
	double max(std::string list);
	void print_result();
public:
	FunctionCell(Cell*(*_table)[MAX_ROWS][MAX_COLUMNS]);
	FunctionCell(std::string _contents, Cell*(*_table)[MAX_ROWS][MAX_COLUMNS]);
	void print();
};