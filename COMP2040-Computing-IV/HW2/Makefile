CC = g++
CFLAGS = -std=c++11 -c -g -Og -Wall -Werror -pedantic
OBJ = PTree.o Square.o
DEPS = PTree.cpp Square.cpp
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
EXE = ptree

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(OBJ) $(EXE)
