all: main.o sortMergeJoin.o radixsort.o quicksort.o read_files.o read_queries.o execute_query.o sums.o updates.o
	gcc main.o sortMergeJoin.o radixsort.o quicksort.o read_files.o read_queries.o execute_query.o sums.o updates.o -o main.exe -pthread -O2

main.o: types.h radixsort.h quicksort.h sortMergeJoin.h read_files.h read_queries.h
	gcc -c main.c -O2

quicksort.o: quicksort.h types.h
	gcc -c quicksort.c -O2

radixsort.o: radixsort.h quicksort.h types.h
	gcc -c radixsort.c -O2

sortMergeJoin.o: sortMergeJoin.h radixsort.h types.h
	gcc -c sortMergeJoin.c -O2

read_files.o: read_files.h types.h
	gcc -c read_files.c -O2

read_queries.o: read_queries.h types.h
	gcc -c read_queries.c -O2

execute_query.o: execute_query.h updates.h sums.h sortMergeJoin.h types.h
	gcc -c execute_query.c -O2

sums.o: sums.h  types.h
	gcc -c sums.c -O2

updates.o: updates.h types.h
	gcc -c updates.c -O2

clean:
	rm -f updates.o
	rm -f sums.o
	rm -f execute_query.o
	rm -f read_queries.o
	rm -f read_files.o
	rm -f main.o
	rm -f sortMergeJoin.o
	rm -f radixsort.o
	rm -f quicksort.o
	rm -f main.exe
	rm -f results.txt
