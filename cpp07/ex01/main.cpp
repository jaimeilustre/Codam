/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 15:18:05 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/09 15:29:27 by jilustre      ########   odam.nl         */
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
	
	int arr[] = {1, 2, 3, 4};
	iter(arr, 4, printElement<int>);

	std::cout << "=== INCREMENTING AN INT ARRAY ===" << std::endl;
	
	iter(arr, 4, increment);
	iter(arr, 4, printElement<int>);
	
	return (0);
}