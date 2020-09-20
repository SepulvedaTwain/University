all: askisi1

askisi1: main1.o askisi1.o ItemType1.o
	gcc main1.o askisi1.o ItemType1.o -o askisi1

main1.o: main1.c 
	gcc -c main1.c

askisi1.o: askisi1.c 
	gcc -c askisi1.c

ItemType1.o: ItemType1.c 
	gcc -c ItemType1.c

clean:
	rm -rf *o askisi1

