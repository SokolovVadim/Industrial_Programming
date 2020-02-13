all:
	g++ main.cpp -o run
valgrind: run
	valgrind --leak-check=yes ./run
clean:
	rm -rf run *.o
