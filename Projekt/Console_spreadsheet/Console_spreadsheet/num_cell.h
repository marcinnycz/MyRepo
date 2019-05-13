#pragma once
#include "cell.h"
#include <string>

class NumericCell: public Cell
{
	
public:
	using Cell::Cell;
	void print();
	double value();
};