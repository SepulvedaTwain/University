OBJS = BitcoinTreeBase.o main.o Database.o SenderReceiver.o
SOURCE = BitcoinTreeBase.cpp main.cpp Database.cpp SenderReceiver.cpp
HEADER = BitcoinTreeBase.h main.h Database.h SenderReceiver.h
OUT = ergasia1
CC = g++
FLAGS = -g -c 


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

BitcoinTreeBase.o: BitcoinTreeBase.cpp
	$(CC) $(FLAGS) BitcoinTreeBase.cpp

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

Database.o: Database.cpp
	$(CC) $(FLAGS) Database.cpp

SenderReceiver.o: SenderReceiver.cpp
	$(CC) $(FLAGS) SenderReceiver.cpp

clean:
	rn -f $(OBJS) $(OUT)
