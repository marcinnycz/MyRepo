#pragma once
#include <iostream>
#include <windows.h>
#include <string>

#define TEXT_FIELD_SIZE 64

class TextField
{
	COORD position;
	std::string contents;
	void clear();
public:
	TextField();
	void enter(std::string _contents);
	void leave();
	void edit();
	std::string get_contents();
};

void set_cursor_visibility(int visible);