myprog.exe: HT.o ht_main_test.o BF_64.a
	gcc HT.o ht_main_test.o BF_64.a -o myprog.exe -static

HT.o: HT.c BF.h
	gcc -c HT.c

main.o: HT.h
	gcc -c ht_main_test.c

clean:
	rm -f SHT.o
	rm -f HT.o
	rm -f main.o
	rm -f ht_main_test.o
	rm -f myprog.exe
	rm -f myFile1
	rm -f primary.index
	rm -f output.txt
	rm -f secondary.index
