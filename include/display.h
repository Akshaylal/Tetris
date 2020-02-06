#ifndef DISPLAY_H
#define DISPLAY_H

class Display: public Shape{
	char screen[ROW][COL]{};
	char vmem[TROW][TCOL];
	char bg;
	int score, level, next_tm, tetris, lines;
	bool over, dtetris;
	clock_t t;
	public:
		void show();
		void copytobg();
		bool isFull();
		bool down();
		bool left();
		bool right();
		void rotate(bool);
		void hardDrop();
		int clearLines();
		void setData(int, int, int, int, bool);
		int getTetris();
			
		Display(){
			bg = ' ';
			over = 0;
			tetris = 0;
			lines = 0;
			dtetris = 0;
			for(int i = 0; i < TROW; ++i)
				for(int j = 0; j < TCOL; ++j)
					vmem[i][j] = ' ';
		}
};

#endif
