SOURCES = tetris.cpp include/*.cpp
FLAGS = -lncurses

all: run

run: tetris
	./tetris

tetris: $(SOURCES)
	g++ $^ $(FLAGS) -o $@

clean:
	rm tetris
