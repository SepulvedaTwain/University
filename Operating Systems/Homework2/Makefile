OBJS = main.o myStructs.o
SOURCE = main.cpp myStructs.cpp
HEADER = main.h myStructs.h
OUT = main
CC = g++
FLAGS = -g -c 


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

myStructs.o: myStructs.cpp
	$(CC) $(FLAGS) myStructs.cpp

clean:
	rm -f $(OBJS) $(OUT)
