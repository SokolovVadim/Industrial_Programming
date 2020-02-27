
#include <iostream>
#include <limits>
#include <climits>

long int read_args(char * str);
void input_array(long* array, long n);
void print_array_of_missing_numbers(long* array, long m, long n);


int main(int argc, char** argv)
{
	if(argc != 3)
    {
        printf("invalid number of args\n");
        exit(EXIT_FAILURE);
    }
	std::cout << "Enter max number & array size:" << std::endl;

	long m = read_args(argv[1]);
	long n = read_args(argv[2]);

	if(n > m)
	{
		std::cout << "Array size is supposed to be less than max number" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	long* array = new long[n];
	
	input_array(array, n);
	print_array_of_missing_numbers(array, m, n);

	delete[] array;
}

/*! \brief convert arg from str to long int
 *   returns read number
 *  \param str argument of command line to be parsed      
 */

long int read_args(char * str)
{
    char* endptr;
    errno = 0;

    long int number = strtol(str, &endptr, 10);


    if ((errno == ERANGE && (number == LONG_MAX || number == LONG_MIN)) || (errno != 0 && number == 0))
    {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (endptr == str)
    {
        fprintf(stderr, "Error!\n");
        exit(EXIT_FAILURE);
    }
    if (*endptr != '\0')
    {
        fprintf(stderr, "Error!\n");
        exit(EXIT_FAILURE);
    }
    return number;
}

/*! \brief read array from CL
 *  \param array
 *  \param n array size 
 */

void input_array(long* array, long n)
{
	for(int i(0); i < n; ++i)
		std::cin >> array[i];
}

/*! \brief prints array of missing numbers in cycle
 *         without storing it into array
 *  \param array
 *  \param m max number
 *  \param n array size 
 */

void print_array_of_missing_numbers(long* array, long m, long n)
{
	std::cout << "Array of missing numbers:" << std::endl;
	for(int i(0); i < m; ++i)
	{
		bool number_found(false);
		for(int j(0); j < n; ++j)
		{
			if(i == array[j])
			{
				number_found = true;
				break;
			}
		}
		if(number_found == false)
			std::cout << i << " ";
	}
	std::cout << std::endl;
}


/*
// stackoverflow
int input_max_number()
{
	int m(0);

	while (std::cout << "Max sequence number:" << std::endl && !(std::cin >> m)) {
    	std::cin.clear(); //clear bad input flag
    	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
    	std::cout << "Invalid input; please re-enter.\n";
	}
	

	std::cout << "Read number: " << m << std::endl;
	return m;
}
// https://www.hackerearth.com/ru/practice/notes/validating-user-input-in-c/
void input()
{
	int num;
	bool valid = false;

	while (!valid)
	{
		valid = true; //Assume the cin will be an integer.

		std::cout << "Enter an integer value: " << std::endl;
		std::cin >> num;

		if(std::cin.fail())
		{
			std::cin.clear(); 
			std::cin.ignore(); 
			std::cout << "Please enter an integer" << std::endl;
			valid = false; 
		}

	}

	std::cout << "You entered: " << num << std::endl;
}

*/

