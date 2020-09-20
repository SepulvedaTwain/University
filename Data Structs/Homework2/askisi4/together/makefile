ifeq ($(CBT_IMPL),pointers)

askisi4: main4.o askisi4Pointers.o ItemType4Pointers.o
	gcc main4.o askisi4Pointers.o ItemType4Pointers.o -o askisi4 -lm

main4.o: main4.c 
	gcc -c main4.c

askisi4Pointers.o: askisi4Pointers.c 
	gcc -c askisi4Pointers.c

ItemType4Pointers.o: ItemType4Pointers.c 
	gcc -c ItemType4Pointers.c

	
else


askisi4: main4.o askisi4Array.o ItemType4Array.o
	gcc main4.o askisi4Array.o ItemType4Array.o -o askisi4

main4.o: main4.c 
	gcc -c main4.c

askisi4Array.o: askisi4Array.c 
	gcc -c askisi4Array.c

ItemType4Array.o: ItemType4Array.c 
	gcc -c ItemType4Array.c

endif

clean:
	rm -rf *o askisi4