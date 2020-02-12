all:
	g++ find_number.cpp -o run
valgrind: run
	valgrind --leak-check=yes ./run
clean:
	rm -rf run *.o
