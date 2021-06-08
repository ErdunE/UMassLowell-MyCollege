CC=gcc
CFLAGS=-Wall --std=c99
OBJECTS=main.o my_string.o
string_driver: main.o my_string.o
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
main.o: main.c my_string.h
	$(CC) $(CFLAGS) -c main.c -o main.o
my_string.o: my_string.c my_string.h
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
clean:
	rm string_driver $(OBJECTS)
