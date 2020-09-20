all: askisi6

askisi6: main6.o askisi6.o ItemType6.o
	gcc main6.o askisi6.o ItemType6.o -o askisi6 -lm

main6.o: main6.c 
	gcc -c main6.c

askisi6.o: askisi6.c 
	gcc -c askisi6.c

ItemType6.o: ItemType6.c 
	gcc -c ItemType6.c

clean:
	rm -rf *o askisi6