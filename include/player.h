#ifndef PLAYER_H
#define PLAYER_H

class Player{
	char name[20];
	int score, lines, level;
	static int highScore;
	
	public:
		void getName();
		void setData(int, int, int);
		static void setHS(int);
		static int getHS();
};

#endif
