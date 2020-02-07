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
#include "include/player.h"

using namespace std;



	    //////////////////////////////
	   //////				   //////
	  //////	   Main  	  //////
	 //////					 //////
	//////////////////////////////

int main(){
	int opt;
	Game g;
	
	do{
		cout<<"\033c\n\n\n";
		cout<<"\t\t\t+--------------------------+\n";
		cout<<"\t\t\t|                          |\n";
		cout<<"\t\t\t|          TETRIS          |\n";
		cout<<"\t\t\t|                          |\n";
		cout<<"\t\t\t+--------------------------+\n";
		cout<<"\t\t\t|                          |\n";
		cout<<"\t\t\t|     1. Play              |\n";
		cout<<"\t\t\t|                          |\n";
		cout<<"\t\t\t|     2. Highscore         |\n";
		cout<<"\t\t\t|                          |\n";
		cout<<"\t\t\t|     0. Exit              |\n";
		cout<<"\t\t\t|                          |\n";
		cout<<"\t\t\t+--------------------------+\n";
		cout<<"\t\t\t: ";
		cin>>opt;
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

