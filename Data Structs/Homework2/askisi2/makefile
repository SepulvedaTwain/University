all: askisi2

askisi2: main2.o askisi2.o ItemType2.o
	gcc main2.o askisi2.o ItemType2.o -o askisi2

main2.o: main2.c 
	gcc -c main2.c

askisi2.o: askisi2.c 
	gcc -c askisi2.c

ItemType2.o: ItemType2.c 
	gcc -c ItemType2.c

clean:
	rm -rf *o askisi2
