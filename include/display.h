// full modify

#ifndef DISPLAY_H
#define DISPLAY_H

#include "settings.h"
#include "defval.h"
#include "tm.h"

class Display{
	Tetromino *sh;
	char *screen;
	char vmem[TROW][TCOL];
	char bg;
	unsigned int score, level, tetris, lines;
	bool over, dtetris;
	clock_t t;
	public:
		void show();
		Display();
		void setData(int, int, int, bool, int, bool);
		void setScreen(Tetromino&, char*, Settings&);
		void clears();
};

#endif