#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <ncurses.h>

#include "include/defval.h"
#include "include/tm.h"
#include "include/display.h"
#include "include/game.h"
#include "include/menu.h"
#include "include/settings.h"
#include "include/sound.h"
#include "include/highscore.h"


using namespace std;


	    //////////////////////////////
	   //////				   //////
	  //////	   Main  	  //////
	 //////					 //////
	//////////////////////////////

int main(){
	int opt;
    Settings set;
	Sound sound(set);
	HS* high;
	Game* g;
	Menu m;
	do{
		opt = m.show(sound);
		switch(opt){
			case 0:break;
			case 1:g = new Game;
				g->play(set, sound);
				delete g;
				break;
			case 2:high = new HS;
    			getchar();
    			getchar();
				delete high;
				break;
            case 3:set.show();
            sound.refresh(set);
            break;
		}
	}while(opt != 0);
	cout<<"\033c";
	return 0;
	
}
