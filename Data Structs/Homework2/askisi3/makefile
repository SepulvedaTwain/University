ifeq ($(BT_IMPL),pointers)

askisi3: main3.o askisi1.o ItemType1.o
	gcc main3.o askisi1.o ItemType1.o -o askisi3

main3.o: main3.c 
	gcc -c main3.c

askisi1.o: askisi1.c 
	gcc -c askisi1.c

ItemType1.o: ItemType1.c 
	gcc -c ItemType1.c

	
else

all: askisi3

askisi3: main3.o askisi2.o ItemType2.o
	gcc main3.o askisi2.o ItemType2.o -o askisi3

main3.o: main3.c 
	gcc -c main3.c

askisi2.o: askisi2.c 
	gcc -c askisi2.c

ItemType2.o: ItemType2.c 
	gcc -c ItemType2.c

endif

clean:
	rm -rf *o askisi3
