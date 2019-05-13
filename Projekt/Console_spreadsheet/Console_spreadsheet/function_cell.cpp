#include "function_cell.h"
#include "num_cell.h"
#include <string>
#include <limits>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>

std::string validate_cell(std::string& text);
int convert_column(std::string& name);
int convert_row(std::string& name);

FunctionCell::FunctionCell(Cell*(*_table)[MAX_ROWS][MAX_COLUMNS]) : Cell(), table(_table), result("")
{

}
FunctionCell::FunctionCell(std::string _contents, Cell*(*_table)[MAX_ROWS][MAX_COLUMNS]) : Cell(), table(_table), result("")
{

}

void FunctionCell::print()
{
	for (unsigned int i = 0; i < contents.length(); i++)
	{
		if (contents.compare(1,4,"SUM(") == 0)
		{
			std::string tmpcont = contents.substr(5);
			std::string first = validate_cell(tmpcont);
			if (first != "")
			{
				if (tmpcont[0] == ':')
				{
					tmpcont.erase(0, 1);
					std::string last = validate_cell(tmpcont);
					if (tmpcont[0] == ')' && first != "" && last != "")
					{
						tmpcont.erase(0, 1);
						if (tmpcont.length() == 0)
						{
							int fcolumn = convert_column(first);
							int frow = convert_row(first);
							int lcolumn = convert_column(last);
							int lrow = convert_row(last);
							if (fcolumn > lcolumn)
							{
								int tmp = fcolumn;
								fcolumn = lcolumn;
								lcolumn = tmp;
							}
							if (frow > lrow)
							{
								int tmp = frow;
								frow = lrow;
								lrow = tmp;
							}
							std::stringstream ss;
							int precision = CELL_WIDTH - (int)std::log10(sum(fcolumn, frow, lcolumn, lrow)) - 3;
							if (precision < 0)
							{
								precision = 0;
							}
							ss << std::fixed << std::setprecision(precision) << sum(fcolumn,frow,lcolumn,lrow);
							ss >> result;
							print_result();
							return;
						}
					}
				}
				if (tmpcont[0] == ',')
				{
					std::string list = "";
					if (first != "")
					{
						list.append(first);
						list.append(",");
						bool again = true;
						while (again)
						{
							again = false;
							tmpcont.erase(0, 1);
							std::string next = validate_cell(tmpcont);
							if (next != "")
							{
								list.append(next);
								list.append(",");
								if (tmpcont[0] == ')') //End
								{
									std::stringstream ss;
									int precision = CELL_WIDTH - (int)std::log10(sum(list)) - 3;
									if (precision < 0)
									{
										precision = 0;
									}
									ss << std::fixed << std::setprecision(precision) << sum(list);
									ss >> result;
									print_result();
									return;
								}
								else if (tmpcont[0] == ',') //Again
								{
									again = true; 
								}
								else
								{
									//Incorrect
								}
							}
						}
					}
				}
			}
		}
		else if (contents.compare(1, 4, "MAX(") == 0)
		{
			std::string tmpcont = contents.substr(5);
			std::string first = validate_cell(tmpcont);
			if (first != "")
			{
				if (tmpcont[0] == ':')
				{
					tmpcont.erase(0, 1);
					std::string last = validate_cell(tmpcont);
					if (tmpcont[0] == ')' && first != "" && last != "")
					{
						tmpcont.erase(0, 1);
						if (tmpcont.length() == 0)
						{
							int fcolumn = convert_column(first);
							int frow = convert_row(first);
							int lcolumn = convert_column(last);
							int lrow = convert_row(last);
							if (fcolumn > lcolumn)
							{
								int tmp = fcolumn;
								fcolumn = lcolumn;
								lcolumn = tmp;
							}
							if (frow > lrow)
							{
								int tmp = frow;
								frow = lrow;
								lrow = tmp;
							}
							std::stringstream ss;
							int precision = CELL_WIDTH - (int)std::log10(max(fcolumn, frow, lcolumn, lrow)) - 3;
							if (precision < 0)
							{
								precision = 0;
							}
							ss << std::fixed << std::setprecision(precision) << max(fcolumn, frow, lcolumn, lrow);
							ss >> result;
							print_result();
							return;
						}
					}
				}
				if (tmpcont[0] == ',')
				{
					std::string list = "";
					if (first != "")
					{
						list.append(first);
						list.append(",");
						bool again = true;
						while (again)
						{
							again = false;
							tmpcont.erase(0, 1);
							std::string next = validate_cell(tmpcont);
							if (next != "")
							{
								list.append(next);
								list.append(",");
								if (tmpcont[0] == ')') //End
								{
									std::stringstream ss;
									int precision = CELL_WIDTH - (int)std::log10(max(list)) - 3;
									if (precision < 0)
									{
										precision = 0;
									}
									ss << std::fixed << std::setprecision(precision) << max(list);
									ss >> result;
									print_result();
									return;
								}
								else if (tmpcont[0] == ',') //Again
								{
									again = true; 
								}
								else
								{
									//Incorrect
								}
							}
						}
					}
				}
			}
		}
		else
		{
			std::string tmp = contents.substr(1);
			std::string first = validate_cell(tmp);
			std::string list = "";
			if (first != "")
			{
				list.append(first);
				list.append(",");
				bool again = true;
				if (tmp[0] != '+')
				{
					again = false;
				}
				while (again)
				{
					again = false;
					tmp.erase(0, 1);
					std::string next = validate_cell(tmp);
					if (next != "")
					{
						list.append(next);
						list.append(",");
						if (tmp.length() == 0) //End
						{
							std::stringstream ss;
							int precision = CELL_WIDTH - (int)std::log10(sum(list)) - 3;
							if (precision < 0)
							{
								precision = 0;
							}
							ss << std::fixed << std::setprecision(precision) << sum(list);
							ss >> result;
							print_result();
							return;
						}
						else if (tmp[0] == '+')
						{
							again = true; //Next
						}
						else
						{
							//Incorrect
						}
					}
				}
			}
		}
		std::string tmp = contents.substr(1);
		std::string first = validate_cell(tmp);
		std::string list = "";
		if (first != "")
		{
			if (tmp.length() == 0)
			{
				list.append(first);
				list.append(",");
				std::stringstream ss;
				int precision = CELL_WIDTH - (int)std::log10(sum(list)) - 3;
				if (precision < 0)
				{
					precision = 0;
				}
				ss << std::fixed << std::setprecision(precision) << sum(list);
				ss >> result;
				print_result();
				return;
			}
		}
		std::cout << "  #NAME?  ";
		return;
	}
	std::cout << "   #UNF!  ";
	return;
}

double FunctionCell::sum(int fcolumn, int frow, int lcolumn, int lrow)
{
	double sum = 0;
	for (int i = fcolumn; i <= lcolumn; i++)
	{
		for (int j = frow; j <= lrow; j++)
		{
			if (typeid(*((*table)[j][i])) == typeid(NumericCell)) //Check if cell is numeric
			{
				NumericCell* ref = (NumericCell*)((*table)[j][i]);
				sum += ref->value();
			}
			if (typeid(*((*table)[j][i])) == typeid(FunctionCell)) //Check if cell is a function cell
			{
				FunctionCell* ref = (FunctionCell*)((*table)[j][i]);
				if (ref != this)
				{
					sum += std::stod(ref->result);
				}
			}
		}
	}
	return sum;
}

double FunctionCell::sum(std::string list)
{
	double sum = 0;
	
	std::string current = list.substr(0,list.find(','));
	while (current != "")
	{
		int column = convert_column(current);
		int row = convert_row(current);
		if (typeid(*((*table)[row][column])) == typeid(NumericCell)) //Check if cell is numeric
		{
			NumericCell* ref = (NumericCell*)((*table)[row][column]);
			sum += ref->value();
		}
		if (typeid(*((*table)[row][column])) == typeid(FunctionCell)) //Check if cell is a function cell
		{
			FunctionCell* ref = (FunctionCell*)((*table)[row][column]);
			if (ref != this)
			{
				sum += std::stod(ref->result);
			}
		}
		list = list.substr(list.find(','));
		list.erase(0, 1);
		current = list.substr(0, list.find(','));
	}
	return sum;
}

double FunctionCell::max(int fcolumn, int frow, int lcolumn, int lrow)
{
	double max = 0 - DBL_MAX;
	for (int i = fcolumn; i <= lcolumn; i++)
	{
		for (int j = frow; j <= lrow; j++)
		{
			if (typeid(*((*table)[j][i])) == typeid(NumericCell)) //Check if cell is numeric
			{
				NumericCell* ref = (NumericCell*)((*table)[j][i]);
				if (max < ref->value())
				{
					max = ref->value();
				}
			}
			if (typeid(*((*table)[j][i])) == typeid(FunctionCell)) //Check if cell is a function cell
			{
				FunctionCell* ref = (FunctionCell*)((*table)[j][i]);
				if (ref != this)
				{
					if (max < std::stod(ref->result))
					{
						max = std::stod(ref->result);
					}
				}
			}
		}
	}
	return max;
}

double FunctionCell::max(std::string list)
{
	double max = 0 - DBL_MAX;

	std::string current = list.substr(0, list.find(','));
	while (current != "")
	{
		int column = convert_column(current);
		int row = convert_row(current);
		if (typeid(*((*table)[row][column])) == typeid(NumericCell)) //Check if cell is numeric
		{
			NumericCell* ref = (NumericCell*)((*table)[row][column]);
			if (max < ref->value())
			{
				max = ref->value();
			}
		}
		if (typeid(*((*table)[row][column])) == typeid(FunctionCell)) //Check if cell is a function cell
		{
			FunctionCell* ref = (FunctionCell*)((*table)[row][column]);
			if (ref != this)
			{
				if (max < std::stod(ref->result))
				{
					max = std::stod(ref->result);
				}
			}
		}
		list = list.substr(list.find(','));
		list.erase(0, 1);
		current = list.substr(0, list.find(','));
	}
	return max;
}

std::string validate_cell(std::string& text)
{
	std::string cell_name = "";
	bool column = false;
	bool row = false;
	while (text[0] > 64 && text[0] < 91)
	{
		cell_name.append(&text[0], 1);
		column = true;
		text.erase(0, 1);
	}
	while (text[0] > 47 && text[0] < 58)
	{
		cell_name.append(&text[0], 1);
		row = true;
		text.erase(0, 1);
	}
	if (row && column)
	{
		return cell_name;
	}
	else
	{
		return "";
	}
}

int convert_column(std::string& name)
{
	int index = 0;
	bool correct = false;
	std::string to_convert = "";
	while (name[0] > 64 && name[0] < 91)
	{
		to_convert.append(&name[0], 1);
		correct = true;
		name.erase(0, 1);
	}
	if (correct)
	{
		int it = 0;
		while (to_convert.length() != 0)
		{
			int mult = 1;
			for (int i = 0; i < it; i++)
			{
				mult *= 26;
			}
			index += (to_convert.back() - 64) * mult;
			to_convert.pop_back();
			it++;
		}
		
		return index;
	}
	else
	{
		return -1;
	}
}

int convert_row(std::string& name)
{
	int index = 0;
	bool correct = false;
	std::string to_convert;
	while (name[0] > 47 && name[0] < 58)
	{
		to_convert.append(&name[0], 1);
		correct = true;
		name.erase(0, 1);
	}
	if (correct)
	{
		index = std::stoi(to_convert);
		return index;
	}
	else
	{
		return -1;
	}
}

void FunctionCell::print_result()
{
	if (result.length() > CELL_WIDTH - 1)
	{
		for (unsigned int i = 0; i < CELL_WIDTH; i++)
		{
			std::cout << "#";
		}
	}
	else
	{
		for (unsigned int i = CELL_WIDTH; i > 0; i--)
		{
			if (i > result.length())
			{
				std::cout << " ";
			}
			else
			{
				std::cout << result[result.length() - i];
			}
		}
	}
}