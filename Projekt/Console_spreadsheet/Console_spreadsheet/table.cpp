#include "table.h"
#include <iostream>
#include <string>
#include <fstream>

Table::Table() : row(0), column(0), s_column(0), s_row(0)
{
	HANDLE hstdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;
	c.X = 0;
	c.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	GetConsoleScreenBufferInfo(hstdOut, &offset);
	
	tab[0][0] = new TextCell();

	//Stworzenie komórek z nazwami kolumn
	for (int i = 1; i < MAX_COLUMNS; i++)
	{
		tab[0][i] = new TextCell("    " + convert(i));
	}
	//Stworzenie komórek z nazwami wierszy
	for (int i = 1; i < MAX_ROWS; i++)
	{
		tab[i][0] = new TextCell(std::to_string(i));
	}
	//Stworzenie pustych komórek (domyœlnie numeryczne)
	for (int i = 1; i < MAX_ROWS; i++)
	{
		for (int j = 1; j < MAX_COLUMNS; j++)
		{
			tab[i][j] = new NumericCell();
		}
	}
}

//Funkcja rysuj¹ca tabelkê na ekranie
void Table::print()
{
	COORD coord;
	coord.X = offset.dwCursorPosition.X;
	coord.Y = offset.dwCursorPosition.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	tab[0][0]->print();
	for (int i = 1; i < 10; i++)
	{
		tab[0][i + s_column]->print();
	}
	std::cout << std::endl;
	for (int i = 1; i < 20; i++)
	{
		tab[i + s_row][0]->print();
		for (int j = 1; j < 10; j++)
		{
			tab[i + s_row][j + s_column]->print();
		}
		std::cout << std::endl;
	}
}

void Table::set_cursor()
{
	//Pobranie informacji o konsoli (pozycji kursora)
	HANDLE hstdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO jump_back;
	GetConsoleScreenBufferInfo(hstdOut, &jump_back);

	//Przesuniêcie kursora na odpowiednie miejsce
	COORD coord;
	//Podœwietlenie komórki zaznaczonej
	coord.X = offset.dwCursorPosition.X + CELL_WIDTH + (column - s_column) * CELL_WIDTH;
	coord.Y = offset.dwCursorPosition.Y + 1 + row - s_row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x70);
	tab[row + 1][column + 1]->print();
	//Podœwietlenie kolumny
	coord.X = offset.dwCursorPosition.X + CELL_WIDTH + (column - s_column) * CELL_WIDTH;
	coord.Y = offset.dwCursorPosition.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	tab[0][column + 1]->print();
	//Podœwietlenie wiersza
	coord.X = offset.dwCursorPosition.X;
	coord.Y = offset.dwCursorPosition.Y + 1 + row - s_row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	tab[row + 1][0]->print();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), jump_back.wAttributes);
}

void Table::add_to_row(int r)
{
	row += r;
	if (row < 0 || row > MAX_ROWS)
	{
		row -= r;
	}
	if (row - s_row > 18)
	{
		s_row = row - 18;
		print();
		set_cursor();
	}
	if (row < s_row)
	{
		s_row = row;
		print();
		set_cursor();
	}
}

void Table::add_to_column(int c)
{
	column += c;
	if (column < 0 || column > MAX_COLUMNS)
	{
		column -= c;
	}
	if (column - s_column > 8)
	{
		s_column = column - 8;
		print();
		set_cursor();
	}
	if (column < s_column)
	{
		s_column = column;
		print();
		set_cursor();
	}
}

std::string Table::get_current_cell_contents()
{
	return tab[row + 1][column + 1]->get_contents();
}

void Table::set_current_cell_contents(std::string _contents)
{
	tab[row + 1][column + 1]->set_contents(_contents);
}

int Table::change_current_cell_type(std::string type)
{
	if (type == "numeric")
	{
		delete tab[row + 1][column + 1];
		tab[row + 1][column + 1] = new NumericCell();
		return 0;
	}
	else if (type == "text")
	{
		delete tab[row + 1][column + 1];
		tab[row + 1][column + 1] = new TextCell();
		return 0;
	}
	else if (type == "function")
	{
		delete tab[row + 1][column + 1];
		tab[row + 1][column + 1] = new FunctionCell(&tab);
		return 0;
	}
	return 1;
}

std::string convert(int index)
{
	std::string tmp;
	index--;
	int st = index;
	if (index < 26)
	{
		tmp.insert(0, 1, index + 65);
	}
	else
	{
		char c = index % 26 + 64;
		while (index > 25)
		{
			tmp.insert(0, 1, c + 1);
			index = index / 26;
			c = index % 26 + 64;
		}
		tmp.insert(0, 1, c);
	}
	return tmp;
}

int Table::save(std::string filename)
{
	std::ofstream myfile;
	// Otwarcie pliku
	myfile.open(filename, std::ios::binary);
	for (int i = 1; i < MAX_ROWS; i++)
	{
		for (int j = 1; j < MAX_COLUMNS; j++)
		{
			if (tab[i][j]->get_contents() != "")
			{
				myfile << i << " " << j << " " << tab[i][j]->get_contents() << std::endl;
			}
		}
	}
	//Zamkniêcie pliku
	myfile.close();
	return 0;
}

int Table::load(std::string filename)
{
	std::ifstream myfile;
	// Otwarcie pliku
	myfile.open(filename, std::ios::binary);
	if(myfile.is_open())
	{
		int tmp, tmp2;
		std::string content;
		while (myfile >> tmp)
		{
			myfile >> tmp2;
			getline(myfile, content);
			content.erase(0, 1);
			if (content[0] == '\'')
			{
				row = tmp - 1;
				column = tmp2 - 1;
				change_current_cell_type("text");
				row = 0;
				column = 0;
			}
			else if (content[0] == '=')
			{
				row = tmp - 1;
				column = tmp2 - 1;
				change_current_cell_type("function");
				row = 0;
				column = 0;
			}
			tab[tmp][tmp2]->set_contents(content);
		}
		//Zamkniêcie pliku
		myfile.close();
		return 0;
	}
	else
	{
		return 1;
	}
}
