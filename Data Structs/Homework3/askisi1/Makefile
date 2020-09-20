OBJS = main.o HTHash.o 
SOURCE = main.c HTHash.c
HEADER = main.h HTHash.h
OUT = demo
CC = gcc
FLAGS = -g -c 


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) 

main.o: main.c
	$(CC) $(FLAGS) main.c

HTHash.o: HTHash.c
	$(CC) $(FLAGS) HTHash.c

clean:
	rn -f $(OBJS) $(OUT)
