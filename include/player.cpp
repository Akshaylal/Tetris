#include <iostream>

#include "player.h"

using namespace std;


void Player::getName(){
	cout<<"Enter name : ";
	cin>>name;
}

void Player::setData(int sc, int le, int li){
	score = sc;
	lines = li;
	level = le;
}

int Player::highScore;

void Player::setHS(int hs){
	highScore = hs;
}

int Player::getHS(){
	return highScore;
}
