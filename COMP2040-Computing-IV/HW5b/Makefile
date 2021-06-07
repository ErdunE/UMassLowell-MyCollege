CC = g++
CFLAGS = -std=c++11 -c -g -Og -Wall -Werror -pedantic
OBJ = GuitarString.o RingBuffer.o GuitarHero.o
DEPS = GuitarString.cpp RingBuffer.cpp GuitarHero.cpp
LIBS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
EXE = GuitarHero

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(OBJ) $(EXE)
