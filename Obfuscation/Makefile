all:
	g++ main.cpp -o run
opponent:
	g++ algorithm.cpp -Wall -o a.out
valgrind: run
	valgrind --leak-check=yes ./run
clean:
	rm -rf run a.out *.o
