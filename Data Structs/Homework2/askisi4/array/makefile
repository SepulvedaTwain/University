all: askisi4

askisi4: main4Array.o askisi4Array.o ItemType4Array.o
	gcc main4Array.o askisi4Array.o ItemType4Array.o -o askisi4

main4Array.o: main4Array.c 
	gcc -c main4Array.c

askisi4Array.o: askisi4Array.c 
	gcc -c askisi4Array.c

ItemType4Array.o: ItemType4Array.c 
	gcc -c ItemType4Array.c

clean:
	rm -rf *o askisi4
