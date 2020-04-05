#include <iostream>
#include "menu.h"

using namespace std;

int Menu::show(){
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
	cout<<"\t\t\t|     3. Settings          |\n";
	cout<<"\t\t\t|                          |\n";
	cout<<"\t\t\t|     0. Exit              |\n";
	cout<<"\t\t\t|                          |\n";
	cout<<"\t\t\t+--------------------------+\n";
	cout<<"\t\t\t: ";
	cin>>opt;
	return opt;
}

int PauseMenu::show(){
	cout<<"\033c\n\n\n";
	cout<<"\t\t\t+--------------------------+\n";
	cout<<"\t\t\t|                          |\n";
	cout<<"\t\t\t|           PAUSE          |\n";
	cout<<"\t\t\t|                          |\n";
	cout<<"\t\t\t+--------------------------+\n";
	cout<<"\t\t\t|                          |\n";
	cout<<"\t\t\t|     1. Resume            |\n";
	cout<<"\t\t\t|                          |\n";
	cout<<"\t\t\t|     2. New Game          |\n";
	cout<<"\t\t\t|                          |\n";
	cout<<"\t\t\t|     0. Exit              |\n";
	cout<<"\t\t\t|                          |\n";
	cout<<"\t\t\t+--------------------------+\n";
	cout<<"\t\t\t: ";
	cin>>opt;
	return opt;
}