#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstdio>
#include <cstring>

#include "display.h"
#include "game.h"
#include "sound.h"
#include "menu.h"
#include "highscore.h"

using namespace std;


	    //////////////////////////////
	   //////				   //////
	  //////	   Game  	  //////
	 //////					 //////
	//////////////////////////////

Game::Game(){
	ifstream s;
    s.open(F_SAV, ios::binary);
    if(s){
        // load from save file
		if(!s.read((char*)this, sizeof(Game))){
            restart();
        }
		s.close();
    }else{
        // new game
		restart();
    }
}

void Game::play(Settings& sett, Sound& snd){
	if(over){
		restart();
	}
	start_display();
	PauseMenu pmenu;
	Display ds;
	char c;
	int collisiond, t_lines = 0;
	int pmenuopt;
	clock_t prev = clock();
	srand(time(0));
	setLevelSpeed();
	next_tm = random_tm();
	ds.setScreen(tm, &screen[0][0], sett);
	while(gameOn){
		collisiond = 0;
        current_tm = next_tm;
		tm.newShape(current_tm);
		next_tm = random_tm();
        tm.nextShape(next_tm);
		ds.setData(score, level, lines, over, tetris, dtetris);
		ds.show();
		over = isFull();
		gameOn = !over;
		while(gameOn == 1 & (collisiond < 2)){
			if(clock() > levelDelay*1000 + prev){
				ds.show();
				collisiond += !down();
				prev = clock();
			}
			if((c = getch()) != ERR){
				switch(c){
					case 'w':if(rotate(0)){
						snd.spin();
					}
					break;
					case 'a':if(left()){
						snd.movelr();
					}
					break;
					case 'd':if(right()){
						snd.movelr();
					}
					break;
					case 's':down();
					break;
					case ' ':hardDrop();
						collisiond = 2;
					break;
					case 27:
						stop_display();
						switch(pmenu.show()){
							case 1:start_display();
							break;
							case 2:restart();
							ds.setData(0, 0, 0, over, 0, 0);
							ds.clears();
							break;
							case 0:save();
							return;
							break;
						}
					break;
				}
				ds.show();
			}
		}
		score += 10*(level+1);
		copytobg();
		snd.hdrop();
		t_lines = clearLines();
		calcScore(t_lines);
		lines += t_lines;
		checkLevel();
		if(t_lines > 0){
			snd.clear();
		}
	}
	snd.gameover();
	del();
	ds.setData(score, level, lines, over, tetris, dtetris);
	ds.show();
	getchar();
	getchar();
	stop_display();
	HS savehs(score);
	snd.bgm();
}

int Game::clearLines(){
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

void Game::copytobg(){
	int i, j;
	for(i = tm.y; i < (tm.yn+tm.y); ++i){
		for(j = tm.x; j < (tm.xn+tm.x); ++j){
			screen[i][j] = (tm.current[i-tm.y][j-tm.x] == 0)?screen[i][j]:tm.current[i-tm.y][j-tm.x];
		}
	}
}

void Game::hardDrop(){
	while(down());
}

bool Game::down(){
	bool fl = 1;
	if(tm.y+tm.yn < ROW){
		for(int i = 0; i < tm.yn; ++i){
			for(int j = 0; j < tm.xn; ++j){
				if(tm.current[i][j] != 0){
					if(screen[tm.y+i+1][tm.x+j] != 0){
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
			++tm.y;
			return 1;
		}
	}
	return 0;
}

bool Game::left(){
	bool fl = 1;
	if(tm.x > 0){
		for(int i = 0; i < tm.yn; ++i){
			for(int j = 0; j < tm.xn; ++j){
				if(tm.current[i][j] != 0){
					if(screen[tm.y+i][tm.x+j-1] != 0){
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
			--tm.x;
			return 1;
		}
	}
	return 0;
}

bool Game::right(){
	bool fl = 1;
	if(tm.x+tm.xn < COL){
		for(int i = 0; i < tm.yn; ++i){
			for(int j = 0; j < tm.xn; ++j){
				if(tm.current[i][j] != 0){
					if(screen[tm.y+i][tm.x+j+1] != 0){
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
			++tm.x;
			return 1;
		}
	}
	return 0;
}

bool Game::isFull(){
	bool fl = 1;
	for(int i = 0; i < tm.yn; ++i){
		for(int j = 0; j < tm.xn; ++j){
			if(tm.current[i][j] != 0){
				if(screen[tm.y+i][tm.x+j] != 0){
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

bool Game::rotate(bool dir){
	bool fl = 1;
	if(tm.rot(dir)){
		fl = isFull();
		if(fl){
			tm.rot(!dir);
		}
	}
	return !fl;
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
	// if(ds.getTetris() == 1){
	// 	y += (y * 50)/ 100;
	// }else if(ds.getTetris() > 1){
	// 	y += y;
	// }
	// score += y;
}

void Game::setLevelSpeed(){
	switch(level){
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

void Game::checkLevel(){
	if(lines > 9)
		level = 1;
	if(lines > 19)
		level = 2;
	if(lines > 29)
		level = 3;
	if(lines > 39)
		level = 4;
	if(lines > 49)
		level = 5;
	if(lines > 59)
		level = 6;
	if(lines > 69)
		level = 7;
	if(lines > 79)
		level = 8;
	if(lines > 89)
		level = 9;
	setLevelSpeed();
}

void Game::start_display(){
	initscr();
	nodelay(stdscr, TRUE);
	clear();
}

void Game::stop_display(){
	endwin();
}

void Game::restart(){
	over = 0;
   	score = 0;
    level = 0;
   	gameOn = 1;
    lines = 0;
	tetris = 0;
	dtetris = 0;
	for(int i = 0; i < ROW; ++i)
		for(int j = 0; j < COL; ++j)
			screen[i][j] = 0;
}

void Game::save(){
    ofstream s;
    s.open("save.dat", ios::binary);
    s.write((char*)this, sizeof(Game));
    s.close();
}

void Game::del(){
	char cmd[20] = "rm ";
	strcat(cmd, F_SAV);
	system(cmd);
}