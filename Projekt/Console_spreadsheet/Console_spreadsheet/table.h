#pragma once
#include "cell.h"
#include "num_cell.h"
#include "text_cell.h"
#include "function_cell.h"
#include <windows.h>

#define MAX_ROWS 512
#define MAX_COLUMNS 128

class Table
{
	CONSOLE_SCREEN_BUFFER_INFO offset;
	HANDLE hstdOut;
	Cell* tab[MAX_ROWS][MAX_COLUMNS];
	int column, row;
	int s_column, s_row;
public:
	Table();
	void print();
	void set_cursor();
	void add_to_row(int r);
	void add_to_column(int c);
	std::string get_current_cell_contents();
	void set_current_cell_contents(std::string _contents);
	int change_current_cell_type(std::string type);
	int save(std::string filename);
	int load(std::string filename);
};

std::string convert(int index);