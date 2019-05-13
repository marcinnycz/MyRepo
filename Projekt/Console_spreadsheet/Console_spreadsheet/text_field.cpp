#include "text_field.h"
#include <conio.h>


TextField::TextField() : contents("")
{
	position.X = 0;
	position.Y = 0;
	HANDLE hstdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO jump_back;
	GetConsoleScreenBufferInfo(hstdOut, &jump_back);

	//TODO
	//Przesuniêcie kursora na odpowiednie miejsce i wypisanie nazwy komórki
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	//std::cout << "A1:";
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), jump_back.dwCursorPosition);
}

void TextField::clear()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	std::cout << std::string(TEXT_FIELD_SIZE, ' ');
}

void TextField::enter(std::string _contents)
{
	set_cursor_visibility(1);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	contents = _contents;
	std::cout << contents;
}

void TextField::leave()
{
	clear();
	set_cursor_visibility(0);
}

void TextField::edit()
{
	char tfc = 0;
	while (tfc != 13)
	{
		if (_kbhit())
		{
			tfc = _getch();
			if (tfc == -32)
			{
				tfc = _getch();
			}
			else if (tfc == 8)
			{
				if (contents.length())
				{
					contents.erase(contents.end() - 1);
				}
			}
			else
			{
				if (tfc != 13 && contents.length() < TEXT_FIELD_SIZE)
				{
					contents.append(1, tfc);
				}
			}
			clear();
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			std::cout << contents;
		}
	}
}

std::string TextField::get_contents()
{
	return contents;
}

void set_cursor_visibility(int visible)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(consoleHandle, &info);
	info.bVisible = visible;
	SetConsoleCursorInfo(consoleHandle, &info);
}