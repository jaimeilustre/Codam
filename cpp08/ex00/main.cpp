/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 15:34:50 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/11 15:58:21 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iostream>

int main(void)
{
	std::vector<int>	v;
	std::deque<int>		d;
	std::list<int>		l;

	std::cout << "=== VECTOR TESTS ===" << std::endl;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	for (int i = 0; i < 3; i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;

	try
	{
		std::vector<int>::iterator it_v = easyfind(v, 3);
		std::cout << "Found in vector: " << *it_v << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Vector: " << e.what() << std::endl;
	}
	return (0);
}