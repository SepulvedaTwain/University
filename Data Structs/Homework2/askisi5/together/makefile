ifeq ($(BH_IMPL),pointers)

askisi5: main5.o askisi5Pointers.o ItemType5Pointers.o
	gcc main5.o askisi5Pointers.o ItemType5Pointers.o -o askisi5 -lm

main5.o: main5.c 
	gcc -c main5.c

askisi5Pointers.o: askisi5Pointers.c 
	gcc -c askisi5Pointers.c

ItemType5Pointers.o: ItemType5Pointers.c 
	gcc -c ItemType5Pointers.c

	
else


askisi5: main5.o askisi5Array.o ItemType5Array.o
	gcc main5.o askisi5Array.o ItemType5Array.o -o askisi5 -lm

main5A.o: main5.c 
	gcc -c main5.c

askisi5Array.o: askisi5Array.c 
	gcc -c askisi5Array.c

ItemType5Array.o: ItemType5Array.c 
	gcc -c ItemType5Array.c

endif

clean:
	rm -rf *o askisi5