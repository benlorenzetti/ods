OBJS = testZip.o
CC = g++
CFLAGS = -std=c++0x -c

test:   $(OBJS)
	$(CC) $(OBJS) -o test

testZip.o: testZip.cpp zip.h
	$(CC) $(CFLAGS) testZip.cpp
