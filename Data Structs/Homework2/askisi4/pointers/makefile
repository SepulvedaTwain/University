all: askisi4

askisi4: main4Pointers.o askisi4Pointers.o ItemType4Pointers.o
	gcc main4Pointers.o askisi4Pointers.o ItemType4Pointers.o -o askisi4 -lm

main4Pointers.o: main4Pointers.c 
	gcc -c main4Pointers.c

askisi4Pointers.o: askisi4Pointers.c 
	gcc -c askisi4Pointers.c

ItemType4Pointers.o: ItemType4Pointers.c 
	gcc -c ItemType4Pointers.c

clean:
	rm -rf *o askisi4