#pragma once
#include "cell.h"

class TextCell: public Cell
{
	
public:
	using Cell::Cell;
	void print();
};