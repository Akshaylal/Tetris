#include <ncurses.h>
#ifndef MENU_H
#define MENU_H

class Menu{
	int opt;
	public:
		int show();
};

class PauseMenu{
	int opt;
	public:
		int show();
};

#endif