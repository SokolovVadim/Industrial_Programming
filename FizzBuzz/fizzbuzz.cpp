
#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

const int MAX_SIZE = 2 << 6;
const int BUF_SIZE = 2 << 10;


const int open_file(const char * fileName, const int flag);
void  read_file(const int fd, char* buff);
void  read_sequence(char* buff);

// uint32_t reduce(uint32_t x, uint32_t N) ;
int mod(int num, int divisor) ;

int main(int argc, char** argv)
{
	// std::cout << "Enter filename:" << std::endl;

	if(argc != 2)
	{
		std::cout << "ERROR!" << std::endl;
		exit(EXIT_FAILURE);
	}

	char* filename = argv[1];
	std::cout << filename << std::endl;
	int fd = open_file(filename, O_RDONLY);

	char* buff = new char[BUF_SIZE];

	read_file(fd, buff);
	read_sequence(buff);
	/*for(int i(0); i < 10; ++i)
	{
		std::cout << mod(i, 3) << std::endl;
	}*/
	
	delete[] buff;
	if(close(fd) < 0)
	{
		printf("close has failed!\n");
	}
}

const int open_file(const char * fileName, const int flag)
{
	int openFlag = open(fileName, flag);	// read & write

	if(openFlag == -1)
	{
		printf("Open failure!\n");
	}

	printf("Opened!\n");
	return openFlag;
}

void read_file(const int fd, char* buff)
{
	size_t sizeBuff = read(fd, buff, MAX_SIZE);// close fd  (get a pointer)

	if(sizeBuff < 0)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}

	buff[sizeBuff - 1] = '\0';

	// printf("Read from file!\n");
	/*printf("buff = %s", buff);
	std::cout << std::endl;*/

	/*if(close(fd) < 0)
	{
		printf("close has failed!\n");
	}*/
	

}

/*
// x % N
uint32_t reduce(uint32_t x, uint32_t N) {
  return ((uint64_t) x * (uint64_t) N) >> 32 ;
}
*/

// num % divisor
int mod(int num, int divisor) 
{ 
    return (num - divisor * (num / divisor)); 
} 

void  read_sequence(char* buff)
{
	std::string str(buff);
	std::cout << str << std::endl;
	std::stringstream stream(str);
	int n(0);
	while(stream >> n)
	{
		n = abs(n);
		if(mod(n, 3) == 0 && mod(n, 5) == 0){
     		std::cout << "FizzBuzz\n";
    	}
    	else if(mod(n, 3) == 0){
      		std::cout << "Fizz\n";
    	}
    	else if(mod(n, 5) == 0){
      		std::cout << "Buzz\n";
    	}
    	else{
      		std::cout << n << "\n";
    	}
	}
}
