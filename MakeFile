CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic
all: ladder dijkstras
ladder: src/ladder_main.cpp ladder.o
	g++ $(CXXFLAGS) src/ladder_main.cpp -o ladder ladder.o

dijkstras: src/dijkstras_main.cpp dijkstras.o
	g++ $(CXXFLAGS) src/dijkstras_main.cpp -o dijkstras dijkstras.o

ladder.o: src/ladder.cpp src/ladder.h
	g++ -c src/ladder.cpp -o ladder.o

dijkstras.o: src/dijkstras.cpp src/dijkstras.h
	g++ -c src/dijkstras.cpp -o dijkstras.o

clean:
	/bin/rm ladder dijkstras