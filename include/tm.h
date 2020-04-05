#ifndef TM_H
#define TM_H

class Tetromino{
	protected:
	const char tetromino[7][2][4] = {
		{{'X', 'X', 'X', 'X'},
		 {0, 0, 0, 0}},
		
		{{0, 'H', 0, 0},
		 {'H', 'H', 'H', 0}},
	 	
		{{'Q', 0, 0, 0},
		 {'Q', 'Q', 'Q', 0}},
		 
		{{0, 0, 'D', 0},
		 {'D', 'D', 'D', 0}},
		 
		{{'N', 'N', 0, 0},
		 {0, 'N', 'N', 0}},
		
		{{0, 'Z', 'Z', 0},
		 {'Z', 'Z', 0, 0}},
		
		{{'O', 'O', 0, 0},
		 {'O', 'O', 0, 0}},
	};
	
	public:
		char current[4][4]{};
		char next[4][4]{};
		int x, y, xn, yn;
		bool rot(bool);

		void newShape(int);
		void nextShape(int);
		
};

#endif