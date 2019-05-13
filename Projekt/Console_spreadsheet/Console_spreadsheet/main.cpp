#include <iostream>
#include <conio.h>
#include "cell.h"
#include "table.h"
#include "text_field.h"


int main()
{
	TextField text_field;
	Table tab;
	int choose_cell = 1, exit = 0;
	tab.load("data.txt");
	set_cursor_visibility(0);
	tab.print();
	tab.set_cursor();

	while (!exit)
	{
		while (choose_cell)
		{
			if (_kbhit())
			{
				tab.print();
				char c = _getch();
				// Przyciśnięto escape
				if (c == 27)
				{
					choose_cell = 0;
					exit = true;
				}
				// W przypadku naciśnięcia strzałki, wyczyszczenie bufora klawiatury ze zbędnego znaku
				if (c == -32)
				{
					c = _getch();
				}
				// Przyciśnięto enter
				if (c == 13)
				{
					choose_cell = 0;
				}
				// Przyciśnięto strzałkę w lewo
				if (c == 75)
				{
					tab.add_to_column(-1);
				}
				// Przyciśnięto strzałkę w prawo
				else if (c == 77)
				{
					tab.add_to_column(1);
				}
				// Przyciśnięto strzałkę w dół
				else if (c == 80)
				{
					tab.add_to_row(1);
				}
				// Przyciśnięto strzałkę w górę
				else if (c == 72)
				{
					tab.add_to_row(-1);
				}
				tab.set_cursor();
			}
		}
		if (exit)
		{
			break;
		}
		text_field.enter(tab.get_current_cell_contents());
		text_field.edit();
		std::string test = text_field.get_contents();
		if (test.length() > 0)
		{
			if (test[0] == '\'')
			{
				tab.change_current_cell_type("text");
			}
			else if (test[0] == '=')
			{
				tab.change_current_cell_type("function");
			}
			else
			{
				tab.change_current_cell_type("numeric");
			}
		}
		tab.set_current_cell_contents(test);
		text_field.leave();
		choose_cell = 1;
		tab.print();
		tab.set_cursor();
	}
	tab.save("data.txt");
	return 0;
}
