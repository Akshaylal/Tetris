#ifndef GAME_H
#define GAME_H

#include "tm.h"
#include "defval.h"
#include "sound.h"

class Game{
    Tetromino tm;
    char screen[ROW][COL]{};

	int current_tm,  next_tm, prev_rand, tetris;
    unsigned int level, levelDelay, lines, score;
	bool over, gameOn, dtetris;
	// Player p;
    int clearLines();
    void copytobg();
    void hardDrop();
    bool down();
    bool left();
    bool right();
    bool isFull();
    bool rotate(bool);
	int random_tm();
	void setLevelSpeed();
	void checkLevel();
	void calcScore(int);
    void start_display();
    void stop_display();
	void restart();
    void save();
    void del();
	public:
		void play(Settings&, Sound&);
		Game();
};

#endif