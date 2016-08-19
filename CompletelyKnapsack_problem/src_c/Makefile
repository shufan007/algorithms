SRC_PATH = src

CXX = g++

objects = test.o Knapsack.o 
test: $(objects)
	$(CXX) -o test $(objects)
Knapsack.o: Knapsack.c Knapsack.h
	$(CXX) -c Knapsack.c
test.o: test.c Knapsack.h
	$(CXX) -c test.c

#gcc -O2 Knapsack.c test.c -o test

## Clean built files
clean:
	rm *.o *.exe *.txt