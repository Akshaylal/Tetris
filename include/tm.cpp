#include "defval.h"
#include "tm.h"
	    //////////////////////////////
	   //////				   //////
	  //////	  Shape 	  //////
	 //////					 //////
	//////////////////////////////

void Tetromino::newShape(int ran){
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			current[i][j] = 0;
	
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 4; ++j)
			current[i][j] = tetromino[ran][i][j];
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

void Tetromino::nextShape(int ran){
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			next[i][j] = 0;
	
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 4; ++j)
			next[i][j] = tetromino[ran][i][j];
}

bool Tetromino::rot(bool dir){
	int t;
	char tsh[4][4]{};
	if((y+xn <= ROW) & (x+yn <= COL)){
		if(dir){
			//anti-clockwise
			for(int i = 0; i < yn; ++i){
				for(int j = 0, jt = xn - 1; j < xn; ++j, --jt){
					tsh[jt][i] = current[i][j];
				}
			}
			for(int i = 0; i < 4; ++i){
				for(int j = 0; j < 4; ++j){
					current[i][j] = tsh[i][j];
				}
			}
		}else{
			//clockwise
			for(int i = 0, it = yn - 1; i < yn; ++i, --it){
				for(int j = 0; j < xn; ++j){
					tsh[j][it] = current[i][j];
				}
			}
			for(int i = 0; i < 4; ++i){
				for(int j = 0; j < 4; ++j){
					current[i][j] = tsh[i][j];
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