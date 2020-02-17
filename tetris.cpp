#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <ncurses.h>


#include "include/defval.h"
#include "include/shape.h"
#include "include/display.h"
#include "include/player.h"
#include "include/game.h"
#include "include/menu.h"
#include "include/intro.h"


using namespace std;



	    //////////////////////////////
	   //////				   //////
	  //////	   Main  	  //////
	 //////					 //////
	//////////////////////////////

int main(){
	int opt;
	Game g;
	Menu m;
	Intro anim;
	anim.show();
	do{
		opt = m.show();
		switch(opt){
			case 0:break;
			case 1:g.play();
			break;
			case 2:break;
		}
	}while(opt != 0);
	cout<<"\033c";
	return 0;
	
}

