CXX = g++
CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

all: dijkstras_main ladder_main main

ladder_main: ladder_main.cpp ladder.cpp
	$(CXX) $(CXXFLAGS) -o ladder_main ladder_main.cpp ladder.cpp

dijkstras_main: dijkstras_main.cpp dijkstras.cpp
	$(CXX) $(CXXFLAGS) -o dijkstras_main dijkstras_main.cpp dijkstras.cpp

main: ladder_main dijkstras_main ladder_main.cpp ladder.cpp dijkstras_main.cpp dijkstras.cpp

clean:
	rm -f dijkstras_main ladder_main main *.o

