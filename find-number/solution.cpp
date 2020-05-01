/*

Copyright (c) April 2020 Vadim Sokolov MIPT

*/


#include <iostream>

void input_array(long* array, long n);
void print_array_of_missing_numbers(long* array, long m, long n);

// ========================================================================

int main(int argc, char** argv)
{
	std::cout << "Enter max number & array size:" << std::endl;

	long m(0), n(0);
	std::cin >> m >> n;

	if(n > m)
	{
		std::cout << "Array size is supposed to be less than max number" << std::endl;
		return EXIT_FAILURE;
	}
	
	long* array = new long[n];
	
	input_array(array, n);
	print_array_of_missing_numbers(array, m, n);

	delete[] array;
	return 0;
}

// ========================================================================

/*! \brief read array from CLs
 *  \param array
 *  \param n array size 
 */

void input_array(long* array, long n)
{
	for(int i(0); i < n; ++i)
		std::cin >> array[i];
}

// ========================================================================

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
