all: run

run: tetris
	./tetris

tetris: tetris.cpp
	g++ $< -lncurses -o $@

clean:
	rm tetris
