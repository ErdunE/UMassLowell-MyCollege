CC = g++
CFLAGS = -std=c++11 -c -g -O2 -Wall -Werror -pedantic
OBJ = main.o ED.o
DEPS = main.cpp ED.cpp
LIBS = -lsfml-system
EXE = ED

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(OBJ) $(EXE)
