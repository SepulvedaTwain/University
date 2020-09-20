OBJS = ReadersWriters.o 
SOURCE = ReadersWriters.cpp
HEADER = ReadersWriters.h
OUT = ReadersWriters
CC = g++
FLAGS = -g -c 


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) -lm

ReadersWriters.o: ReadersWriters.cpp
	$(CC) $(FLAGS) ReadersWriters.cpp

clean:
	rn -f $(OBJS) $(OUT)
