#Makefile for assignment 5

CC = g++
WFLAG = -w
OFLAG = -o
DFLAG = -ggdb
VFLAG = -std=c++11


test: A4-tests.cpp  tombstones.h
	${CC} ${VFLAG} ${WFLAG} tombstones.h A4-tests.cpp  ${OFLAG} A4-tests


.PHONY: clean

clean:
	rm A4-tests
