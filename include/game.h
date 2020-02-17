#ifndef GAME_H
#define GAME_H

class Game{
	int prev_rand, score, level, levelDelay, next_tm, lines;
	bool over, gameOn;
	Display ds;
	Player p;
	int random_tm();
	void setLevelSpeed();
	void checkLevel();
	void calcScore(int);
	
	public:
		void play();
		Game(){
			prev_rand = 6;
			score = 0;
			level = 0;
			gameOn = 1;
			lines = 0;
		}
};

#endif
