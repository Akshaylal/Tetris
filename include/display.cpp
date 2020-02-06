#include <ctime>
#include <cstring>
#include <cstdio>
#include <ncurses.h>

#include "defval.h"
#include "shape.h"
#include "display.h"

		//////////////////////////////
		//////					//////
		//////		Display		//////
		//////					//////
		//////////////////////////////

void Display::show(){
	int i, j;
	char temp[ROW][COL]{};
	char str_score[20], str_level[10], str_lines[15];
	//play
	for(i = 0; i < ROW; ++i){
		for(j = 0; j < COL; ++j){
			temp[i][j] = screen[i][j];
		}
	}
	for(i = y; i < (yn+y); ++i){
		for(j = x; j < (xn+x); ++j){
			temp[i][j] = (shape[i-y][j-x] == 0)?temp[i][j]:shape[i-y][j-x];
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
			vmem[STATR + i][STATC + 2 * j] = (tetromino[next_tm][i][j] != 0)?tetromino[next_tm][i][j]:' ';
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
		memcpy(&vmem[ROW / 2    ][COL - 1], "                    ", 20);
		memcpy(&vmem[ROW / 2 + 1][COL - 1], "     GAME OVER!     ", 20);
		memcpy(&vmem[ROW / 2 + 2][COL - 1], "                    ", 20);
	}
	
	//Tetris status
	if(tetris == 1 & dtetris){
		// Tetris!!
		memcpy(&vmem[STATR + 15][STATC], "Tetris !", 8);
		t = clock();
		dtetris = 0;
	}else if(tetris > 1 & dtetris){
		// Back to back Tetris!!!
		memcpy(&vmem[STATR + 15][STATC], "Back to Back", 12);
		memcpy(&vmem[STATR + 16][STATC], "  Tetris !  ", 12);
		t = clock();
		dtetris = 0;
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

void Display::copytobg(){
	int i, j;
	for(i = y; i < (yn+y); ++i){
		for(j = x; j < (xn+x); ++j){
			screen[i][j] = (shape[i-y][j-x] == 0)?screen[i][j]:shape[i-y][j-x];
		}
	}
}

bool Display::down(){
	bool fl = 1;
	if(y+yn < ROW){
		for(int i = 0; i < yn; ++i){
			for(int j = 0; j < xn; ++j){
				if(shape[i][j] != 0){
					if(screen[y+i+1][x+j] != 0){
						fl = 0;
						break;
					}
				}
			}
			if(!fl){
				break;
			}
		}
		if(fl){
			++y;
			return 1;
		}
	}
	return 0;
}

bool Display::left(){
	bool fl = 1;
	if(x > 0){
		for(int i = 0; i < yn; ++i){
			for(int j = 0; j < xn; ++j){
				if(shape[i][j] != 0){
					if(screen[y+i][x+j-1] != 0){
						fl = 0;
						break;
					}
				}
			}
			if(!fl){
				break;
			}
		}
		if(fl){
			--x;
			return 1;
		}
	}
	return 0;
}

bool Display::right(){
	bool fl = 1;
	if(x+xn < COL){
		for(int i = 0; i < yn; ++i){
			for(int j = 0; j < xn; ++j){
				if(shape[i][j] != 0){
					if(screen[y+i][x+j+1] != 0){
						fl = 0;
						break;
					}
				}
			}
			if(!fl){
				break;
			}
		}
		if(fl){
			++x;
			return 1;
		}
	}
	return 0;
}

void Display::hardDrop(){
	while(down());
}

void Display::rotate(bool dir){
	bool fl = 1;
	if(rot(dir)){
		fl = isFull();
		if(fl){
			rot(!dir);
		}
	}
}

bool Display::isFull(){
	bool fl = 1;
	for(int i = 0; i < yn; ++i){
		for(int j = 0; j < xn; ++j){
			if(shape[i][j] != 0){
				if(screen[y+i][x+j] != 0){
					fl = 0;
					break;
				}
			}
		}
		if(!fl){
			break;
		}
	}
	return !fl;
}

int Display::clearLines(){
	int count = 0;
	bool fl;
	for(int i = ROW - 1; i > 0; --i){
		fl = 1;
		for(int j = 0; j < COL; ++j){
			if(screen[i][j] == 0){
				fl = 0;
				break;
			}
		}
		if(fl){
			count++;
			for(int k = i; k > 0; --k)
				for(int j = 0; j < COL; ++j)
					screen[k][j] = screen[k-1][j];
			++i;
		}
	}
	if(count > 0){
		if(count == 4){
			tetris++;
			dtetris = 1;
		}else{
			tetris = 0;
		}
	}
	return count;
}

void Display::setData(int sc, int l, int tm, int li, bool ov){
	score = sc;
	level = l;
	over = ov;
	next_tm = tm;
	lines += li;
}

int Display::getTetris(){
	return tetris;
}
