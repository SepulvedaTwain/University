OBJS = MyStructs.o Server.o 
SOURCE = MyStructs.cpp Server.cpp
HEADER = MyStructs.h Server.h
OUT = dropbox_server
CC = g++
FLAGS = -g -c 


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) -lpthread

MyStructs.o: MyStructs.cpp
	$(CC) $(FLAGS) MyStructs.cpp

Server.o: Server.cpp
	$(CC) $(FLAGS) Server.cpp

clean:
	rn -f $(OBJS) $(OUT)
