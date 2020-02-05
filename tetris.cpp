#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <ncurses.h>


#define ROW 21
#define COL 10

#define ROWOFF 1
#define COLOFF 8

#define TROW 24
#define TCOL 79

#define STATR 2
#define STATC 40



using namespace std;

class Shape{
	protected:
	const char tetromino[7][2][4] = {
		{{'X', 'X', 'X', 'X'},
		 {0, 0, 0, 0}},
		
		{{0, 'H', 0, 0},
		 {'H', 'H', 'H', 0}},
	 	
		{{'Q', 0, 0, 0},
		 {'Q', 'Q', 'Q', 0}},
		 
		{{0, 0, 'D', 0},
		 {'D', 'D', 'D', 0}},
		 
		{{'N', 'N', 0, 0},
		 {0, 'N', 'N', 0}},
		
		{{0, 'Z', 'Z', 0},
		 {'Z', 'Z', 0, 0}},
		
		{{'O', 'O', 0, 0},
		 {'O', 'O', 0, 0}},
	};
	
	protected:
		char shape[4][4]{};
		int x, y, xn, yn;
		bool rot(bool);
	public:
		void newShape(int);
		
};

class Display: public Shape{
	char screen[ROW][COL]{};
	char vmem[TROW][TCOL];
	char bg;
	int score, level, next_tm;
	bool over;
	public:
		void show();
		void copytobg();
		bool isFull();
		bool down();
		bool left();
		bool right();
		void rotate(bool);
		void hardDrop();
		int clearLines();
		void setData(int, int, int, bool);
			
		Display(){
			bg = '.';
			over = 0;
			for(int i = 0; i < TROW; ++i)
				for(int j = 0; j < TCOL; ++j)
					vmem[i][j] = ' ';
		}
};

class Player{
	char name[20];
	unsigned int score;
	
	public:
		void setName(){cin>>name;}
		void setScore(int x){score = x;}
		int getScore(){return score;}
		
		Player(){score = 0;}
};

class Game{
	int prev_rand, score, level, levelDelay;
	bool tetris;
	
	int random_tm();
	void setLevelSpeed(int);
	void calcScore(int);
	
	public:
		void play();
		Game(){prev_rand = 6; score = 0; level = 0; tetris = 0;}
};

	    //////////////////////////////
	   //////				   //////
	  //////	   Main  	  //////
	 //////					 //////
	//////////////////////////////

int main(){
	Game g;
	g.play();
	return 0;
	
}

	    //////////////////////////////
	   //////				   //////
	  //////	   Game  	  //////
	 //////					 //////
	//////////////////////////////

void Game::play(){
	bool over, gameOn = 1;
	char c;
	int collisiond, next_tm;
	clock_t prev = clock();
	Display ds;
	srand(time(0));
	setLevelSpeed(level);
	initscr();
	nodelay(stdscr, TRUE);
	clear();
	next_tm = random_tm();
	while(gameOn){
		collisiond = 0;
		ds.newShape(next_tm);
		next_tm = random_tm();
		ds.setData(score, level, next_tm, 0);
		ds.show();
		over = ds.isFull();
		gameOn = !over;
		while(gameOn == 1 & (collisiond < 2)){
			if(clock() > levelDelay*1000 + prev){
				ds.show();
				collisiond += !ds.down();
				prev = clock();
			}
			if((c = getch()) != ERR){
				switch(c){
					case 'w':ds.rotate(0);
					break;
					case 'a':ds.left();
					break;
					case 'd':ds.right();
					break;
					case 's':ds.down();
					break;
					case ' ':ds.hardDrop();
						collisiond = 2;
					break;
					case 27:gameOn = 0;
					break;
				}
				ds.show();
			}
		}
		score += 10*(level+1);
		ds.copytobg();
		calcScore(ds.clearLines());
	}
	ds.setData(score, level, next_tm, over);
	ds.show();
	getchar();
	
	endwin();
}

int Game::random_tm(){
	int x = rand() % 7;
	while(prev_rand == x)
		x = rand() % 7;
	prev_rand = x;
	return x;
}

void Game::calcScore(int n){
	int y;
	switch(n){
		case 1:y = 50 * (level + 1);
		tetris = 0;
		break;
		case 2:y = 150 * (level + 1);
		tetris = 0;
		break;
		case 3:y = 350 * (level + 1);
		tetris = 0;
		break;
		case 4:y = 1000 * (level + 1);
		tetris = 1;
		break;
	}
	if(tetris){
		y += (y * 50)/ 100;
	}
	score += y;
}

void Game::setLevelSpeed(int l){
	switch(l){
		case 0:levelDelay = 800;
		break;
		case 1:levelDelay = 720;
		break;
		case 2:levelDelay = 630;
		break;
		case 3:levelDelay = 550;
		break;
		case 4:levelDelay = 470;
		break;
		case 5:levelDelay = 380;
		break;
		case 6:levelDelay = 300;
		break;
		case 7:levelDelay = 220;
		break;
		case 8:levelDelay = 130;
		break;
		case 9:levelDelay = 100;
		break;
	}
}


		//////////////////////////////
		//////					//////
		//////		Display		//////
		//////					//////
		//////////////////////////////

void Display::show(){
	int i, j;
	char temp[ROW][COL]{};
	char str_score[20], str_level[10];
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
	
	//score, level
	sprintf(str_score, "Score : %d", score);
	sprintf(str_level, "Level : %d", level);
	memcpy(&vmem[STATR + 5][STATC - 3], str_score, strlen(str_score));
	memcpy(&vmem[STATR + 8][STATC - 3], str_level, strlen(str_level));
	
	//Game Over
	if(over){
		memcpy(&vmem[ROW / 2    ][COL - 1], "                    ", 20);
		memcpy(&vmem[ROW / 2 + 1][COL - 1], "     GAME OVER!     ", 20);
		memcpy(&vmem[ROW / 2 + 2][COL - 1], "                    ", 20);
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
	return count;
}

void Display::setData(int sc, int l, int tm, bool ov){
	score = sc;
	level = l;
	over = ov;
	next_tm = tm;
}

	    //////////////////////////////
	   //////				   //////
	  //////	  Shape 	  //////
	 //////					 //////
	//////////////////////////////

void Shape::newShape(int ran){
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			shape[i][j] = 0;
	
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 4; ++j)
			shape[i][j] = tetromino[ran][i][j];
	x = (COL / 2) - 1;
	y = 1;
	switch(ran){
		case 0:xn = 4; yn = 1;
		break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:xn = 3; yn = 2;
		break;
		case 6:xn = 2; yn = 2;
	}
}

bool Shape::rot(bool dir){
	int t;
	char tsh[4][4]{};
	if((y+xn <= ROW) & (x+yn <= COL)){
		if(dir){
			//anti-clockwise
			for(int i = 0; i < yn; ++i){
				for(int j = 0, jt = xn - 1; j < xn; ++j, --jt){
					tsh[jt][i] = shape[i][j];
				}
			}
			for(int i = 0; i < 4; ++i){
				for(int j = 0; j < 4; ++j){
					shape[i][j] = tsh[i][j];
				}
			}
		}else{
			//clockwise
			for(int i = 0, it = yn - 1; i < yn; ++i, --it){
				for(int j = 0; j < xn; ++j){
					tsh[j][it] = shape[i][j];
				}
			}
			for(int i = 0; i < 4; ++i){
				for(int j = 0; j < 4; ++j){
					shape[i][j] = tsh[i][j];
				}
			}
		}
		t = xn;
		xn = yn;
		yn = t;
		return 1;
	}else{
		return 0;
	}
}
