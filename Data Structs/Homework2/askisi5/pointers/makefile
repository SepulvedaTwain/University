all: askisi5

askisi5: main5Pointers.o askisi5Pointers.o ItemType5Pointers.o
	gcc main5Pointers.o askisi5Pointers.o ItemType5Pointers.o -o askisi5 -lm

main5Pointers.o: main5Pointers.c 
	gcc -c main5Pointers.c

askisi5Pointers.o: askisi5Pointers.c 
	gcc -c askisi5Pointers.c

ItemType5Pointers.o: ItemType5Pointers.c 
	gcc -c ItemType5Pointers.c

clean:
	rm -rf *o askisi5