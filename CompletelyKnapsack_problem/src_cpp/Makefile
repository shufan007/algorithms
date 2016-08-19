SRC_PATH = src

CXX = g++

objects = test.o Knapsack.o 
test: $(objects)
	$(CXX) -o test $(objects)
Knapsack.o: Knapsack.cpp Knapsack.hpp
	$(CXX) -c Knapsack.cpp
test.o: test.cpp Knapsack.hpp
	$(CXX) -c test.cpp

#gcc -O2 Knapsack.cpp test.cpp -o test

## Clean built files
clean:
	rm *.o *.exe *.txt