#include "text_cell.h"
#include <string>
#include <iostream>


void TextCell::print()
{
	if (contents.length() < 12)
	{
		if (contents.length() > 0)
		{
			if (contents[0] != '\'')
			{
				for (unsigned int i = 0; i < 10; i++)
				{
					if (i < contents.length())
					{
						std::cout << contents[i];
					}
					else
					{
						std::cout << " ";
					}
				}
			}
			else
			{
				for (unsigned int i = 0; i < 10; i++)
				{
					if (i < contents.length())
					{
						std::cout << contents[i + 1];
					}
					else
					{
						std::cout << " ";
					}
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < 10; i++)
			{
				std::cout << " ";
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < 9; i++)
		{
			std::cout << contents[i+1];
		}
		std::cout << (char)175;
	}
}