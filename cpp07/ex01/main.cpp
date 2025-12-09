/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 15:18:05 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/09 16:08:15 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

// Const reference
template <typename T> void printElement(const T& element)
{
	std::cout << element << std::endl;
}

// Non-const reference
void increment(int& i)
{
	i++;	
}

int main(void)
{
	std::cout << "=== TESTING WITH AN INT ARRAY ===" << std::endl;
	
	int arr[] = {1, 2, 3, 4, 5};
	iter(arr, 5, printElement<int>);

	std::cout << "=== INCREMENTING AN INT ARRAY ===" << std::endl;
	
	iter(arr, 5, increment);
	iter(arr, 5, printElement<int>);

	std::cout << "=== TESTING WITH A STRING ARRAY ===" << std::endl;

	std::string array[] = {"hello", "world", "my", "name", "is", "Jaime"};
	iter(array, 6, printElement<std::string>);

	std::cout << "=== TESTING WITH A CONST ARRAY ===" << std::endl;
	
	const int constArr[] = {1, 2, 3, 4, 5};
	iter(constArr, 5, printElement<int>);
	
	return (0);
}