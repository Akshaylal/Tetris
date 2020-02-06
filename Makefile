SOURCES = tetris.cpp include/shape.cpp include/display.cpp include/game.cpp
FLAGS = -lncurses

all: run

run: tetris
	./tetris

tetris: $(SOURCES)
	g++ $^ $(FLAGS) -o $@

clean:
	rm tetris
