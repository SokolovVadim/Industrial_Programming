#include <iostream>
​
template <typename T>
void func(T* array, int& replace_index, int& first, int& second, int index)
{
	replace_index = rand() % (second - first + 1) + first;
	std::swap(array[first], array[replace_index]);
	int i, j;
	i = second;
	j = second;
	while(j > first)
	{
		if(array[j] <= array[first])
		{
			j--;
		}
		if(array[j] > array[first])
		{
			std::swap(array[i], array[j]);
			i--;																																															j--;
		}
​
	}
	replace_index = i;
	std::swap(array[i], array[j]);
	if(replace_index < index)
	{
		first = replace_index + 1;
	}
	if(replace_index > index)
	{
		second = replace_index - 1;
	}
}
​
int main()
{
	int n = 0, index = 0;
	int replace_index = 0;
	std::cin >> n >> index;
	int first = 0, second = n - 1;
	int* array = new int [n];
	for(int i = 0; i < n; i++)
		std::cin >> array[i];                                                                                                                                                               func(array, replace_index, first, second, index);
	while(replace_index != index)
	{
		func(array, replace_index, first, second, index);
	}                                                                                                                                                                                                                                                                                                                                                                                                                                          std::cout << array[replace_index] << '\n';
	delete [] array;
	return 0;
}