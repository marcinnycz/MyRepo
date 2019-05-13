#include "cell.h"
#include <string>
#include <iostream>

Cell::Cell() : contents("")
{
}

Cell::Cell(std::string _contents) : contents(_contents)
{
}

std::string Cell::get_contents()
{
	return contents;
}

void Cell::set_contents(std::string _contents)
{
	contents = _contents;
}