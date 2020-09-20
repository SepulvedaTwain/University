all: askisi5

askisi5: main5Array.o askisi5Array.o ItemType5Array.o
	gcc main5Array.o askisi5Array.o ItemType5Array.o -o askisi5 -lm

main5Array.o: main5Array.c 
	gcc -c main5Array.c

askisi5Array.o: askisi5Array.c 
	gcc -c askisi5Array.c

ItemType5Array.o: ItemType5Array.c 
	gcc -c ItemType5Array.c

clean:
	rm -rf *o askisi5