#pragma once
#include <string>

#define CELL_WIDTH 10

class Cell
{
protected:
	std::string contents;
public:
	Cell();
	Cell(std::string _contents);
	virtual void print() = 0;
	virtual std::string get_contents();
	virtual void set_contents(std::string _contents);
};