OBJS = Client.o MyStructs.o
SOURCE = Client.cpp MyStructs.cpp
HEADER = Client.h MyStructs.h
OUT = dropbox_client
CC = g++
FLAGS = -g -c 


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) -lpthread

Client.o: Client.cpp
	$(CC) $(FLAGS) Client.cpp

MyStructs.o: MyStructs.cpp
	$(CC) $(FLAGS) MyStructs.cpp



clean:
	rn -f $(OBJS) $(OUT)
