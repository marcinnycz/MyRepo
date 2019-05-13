#include "num_cell.h"
#include <string>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <sstream> // stringstream

void NumericCell::print()
{
	if (contents.length() > 0)
	{
		double test;
		try
		{
			 test = std::stod(contents);
		}
		catch (std::exception&)
		{
			std::cout << " #STX_ERR ";
			return;
		}

		std::string con = "";
		bool dd = false;
		for (unsigned int i = 0; i < contents.length(); i++)
		{
			if ((contents[i] > 47 && contents[i] < 58) || contents[i] == '.')
			{
				if (contents[i] == '.')
				{
					if (dd)
					{
						if (con.back() == '.')
						{
							con.pop_back();
						}
						break;
					}
					dd = true;
				}
				con.append(&contents[i], 1);
			}
			else
			{
				break;
			}
		}
		
		if (con.length() < CELL_WIDTH)
		{
			for (unsigned int i = CELL_WIDTH; i > 0; i--)
			{
				if (i > con.length())
				{
					std::cout << " ";
				}
				else
				{
					std::cout << con[con.length() - i];
				}
			}
		}
		else
		{
			bool dot = false;
			for (int i = 0; i < CELL_WIDTH; i++)
			{
				if (con[i] == '.')
				{
					dot = true;
					break;
				}
			}
			if (dot)
			{
				std::cout << " ";
				for (unsigned int i = 0; i < CELL_WIDTH-2; i++)
				{
					std::cout << con[i];
				}
				std::cout << (char)175;
			}
			else 
			{
				for (unsigned int i = 0; i < CELL_WIDTH; i++)
				{
					std::cout << "#";
				}
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < CELL_WIDTH; i++)
		{
			std::cout << ' ';
		}
	}
}

double NumericCell::value()
{
	if (contents != "")
	{
		return std::stod(contents);
	}
	else
	{
		return 0;
	}
}
