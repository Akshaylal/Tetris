// full modify

#include <ctime>
#include <cstring>
#include <cstdio>
#include <ncurses.h>

#include "settings.h"
#include "display.h"

		//////////////////////////////
		//////					//////
		//////		Display		//////
		//////					//////
		//////////////////////////////

Display::Display(){
	over = false;
	bg = ' ';
	for(int i = 0; i < TROW; ++i)
		for(int j = 0; j < TCOL; ++j)
			vmem[i][j] = ' ';
}

void Display::show(){
	int i, j;
	char temp[ROW][COL]{};
	char str_score[20], str_level[10], str_lines[15];
	//play
	for(i = 0; i < ROW; ++i){
		for(j = 0; j < COL; ++j){
			temp[i][j] = *(screen + (i * COL) + (j));
		}
	}
	for(i = sh->y; i < (sh->yn+sh->y); ++i){
		for(j = sh->x; j < (sh->xn+sh->x); ++j){
			temp[i][j] = (sh->current[i-sh->y][j-sh->x] == 0)?temp[i][j]:sh->current[i-sh->y][j-sh->x];
		}
	}
	for(i = 0; i < COL+1; ++i){
		vmem[ROWOFF][COLOFF + 2 * i ] = '_';
		vmem[ROWOFF + ROW][COLOFF + i] = '-';
		vmem[ROWOFF + ROW][COLOFF + i + COL] = '-';
	}
	for(i = 1; i < ROW; ++i){
		vmem[ROWOFF + i][COLOFF - 1] = '|';
		vmem[ROWOFF + i][COLOFF + 2*COL + 1] = '|';
		for(j = 0; j < COL; ++j){
			vmem[ROWOFF + i][COLOFF + 2 * j] = ' ';
			vmem[ROWOFF + i][COLOFF + 2 * j + 1] = (temp[i][j] != 0)?temp[i][j]:bg;
		}
	}
	// next shape
	for(i = 0; i < 2; ++i){
		for(j = 0; j < 4; ++j){
			vmem[STATR + i][STATC + 2 * j] = (sh->next[i][j] != 0)?sh->next[i][j]:' ';
		}
	}
	
	//score, level, lines
	sprintf(str_score, "Score : %d", score);
	sprintf(str_level, "Level : %d", level);
	sprintf(str_lines, "Lines : %d", lines);
	memcpy(&vmem[STATR + 5][STATC], str_score, strlen(str_score));
	memcpy(&vmem[STATR + 7][STATC], str_level, strlen(str_level));
	memcpy(&vmem[STATR + 9][STATC], str_lines, strlen(str_lines));
	
	//Game Over
	if(over){
		memcpy(&vmem[ROWOFF + (ROW / 2 - 1)][COLOFF + 1], "                    ", 20);
		memcpy(&vmem[ROWOFF + (ROW / 2 + 0)][COLOFF + 1], "     GAME OVER!     ", 20);
		memcpy(&vmem[ROWOFF + (ROW / 2 + 1)][COLOFF + 1], "                    ", 20);
	}
	
	//Tetris status
	if(tetris == 1 & dtetris){
		// Tetris!!
		memcpy(&vmem[STATR + 15][STATC], "Tetris !", 8);
		t = clock();
	}else if(tetris > 1 & dtetris){
		// Back to back Tetris!!!
		memcpy(&vmem[STATR + 15][STATC], "Back to Back", 12);
		memcpy(&vmem[STATR + 16][STATC], "  Tetris !  ", 12);
		t = clock();
	}
	if(clock() > 2000000 + t){
		memcpy(&vmem[STATR + 15][STATC], "            ", 12);
		memcpy(&vmem[STATR + 16][STATC], "            ", 12);
	}
	
	// print to screen
	clear();
	for(i = 0; i < TROW; ++i){
		for(j = 0; j < TCOL; ++j){
			printw("%c", vmem[i][j]);
		}
		printw("\n");
	}
	refresh();
}

void Display::setScreen(Tetromino &m, char *c, Settings& sett){
	screen = c;
	sh = &m;
	bg = sett.bg?'.':' ';
}

void Display::setData(int sc, int le, int li, bool ov, int t, bool dt){
	score = sc;
	level = le;
	lines = li;
	over = ov;
	tetris = t;
	dtetris = dt;
}

void Display::clears(){
	for(int i = 0; i < TROW; ++i)
		for(int j = 0; j < TCOL; ++j)
			vmem[i][j] = ' ';
}