#include <ncurses.h>
#include <cstdlib>
#include <ctime>

#include "defval.h"
#include "shape.h"
#include "display.h"
#include "game.h"

	    //////////////////////////////
	   //////				   //////
	  //////	   Game  	  //////
	 //////					 //////
	//////////////////////////////

void Game::play(){
	char c;
	int collisiond;
	clock_t prev = clock();
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
		ds.setData(score, level, next_tm, lines, 0);
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
		lines = ds.clearLines();
		calcScore(lines);
	}
	ds.setData(score, level, next_tm, lines, over);
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
		break;
		case 2:y = 150 * (level + 1);
		break;
		case 3:y = 350 * (level + 1);
		break;
		case 4:y = 1000 * (level + 1);
		break;
	}
	if(ds.getTetris() == 1){
		y += (y * 50)/ 100;
	}else if(ds.getTetris() > 1){
		y += y;
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
