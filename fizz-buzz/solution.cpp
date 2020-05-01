/*

Copyright (c) April 2020 Vadim Sokolov MIPT

*/

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void read_sequence(std::string & str);
unsigned int mod3 (unsigned int a );
unsigned int mod5 (unsigned int a );

// ========================================================================

int main(int argc, char** argv)
{
	std::string str;
	std::getline(std::cin, str);
	read_sequence(str);
}

// ========================================================================

/*! \brief performs mod3 operation 
 *   via binary operations
 *  \param a number to be moded   
 */

unsigned int mod3( unsigned int a ) {
    while (a > 5) {
        int s = 0; /* accumulator for the sum of the digits */
        while (a != 0) {
            s = s + (a & 3);
            a = a >> 2;
        }
        a = s;
    }
    /* note, at this point: a < 6 */
    if (a > 2) a = a - 3;
    return a;
}

// ========================================================================

/*! \brief performs mod5 operation 
 *   via binary operations
 *  \param a number to be moded   
 */

unsigned int mod5( unsigned int a ) {
    while (a > 9) {
        int s = 0; /* accumulator for the sum of the digits */
        while (a != 0) {
            s = s + (a & 7);
            a = (a >> 3) * 3;
        }
        a = s;
    }
    /* note, at this point: a < 10 */
    if (a > 4) a = a - 5;
    return a;
}

// ========================================================================

/*! \brief convert arg from str to int
 *   and prints fizz buzz
 *  \param str argument of command line to be parsed      
 */

void  read_sequence(std::string & str)
{
	std::stringstream stream(str);
	int n(0);
	while(stream >> n)
	{
		n = abs(n);
		if(mod3(n) == 0 && mod5(n) == 0){
     		std::cout << "FizzBuzz\n";
    	}
    	else if(mod3(n) == 0){
      		std::cout << "Fizz\n";
    	}
    	else if( mod5(n) == 0){
      		std::cout << "Buzz\n";
    	}
    	else{
      		std::cout << n << "\n";
    	}
	}
}
