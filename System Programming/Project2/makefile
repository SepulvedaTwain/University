all: mirror_client

mirror_client: main.o lists.o
	g++ main.o lists.o -o mirror_client

main.o: main.cpp
	g++ -c main.cpp

lists.o: lists.cpp
	g++ -c lists.cpp


clean:
	rm -rf *o mirror_client
