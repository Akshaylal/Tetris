#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <ncurses.h>

#include "include/defval.h"
#include "include/shape.h"
#include "include/display.h"
#include "include/game.h"


using namespace std;


class Player{
	char name[20];
	unsigned int score;
	
	public:
		void setName(){cin>>name;}
		void setScore(int x){score = x;}
		int getScore(){return score;}
		
		Player(){score = 0;}
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

