/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 15:34:50 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/11 16:27:34 by jilustre      ########   odam.nl         */
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

	for (int i : v)
		std::cout << i << " ";
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

	std::cout << "=== DEQUE TESTS ===" << std::endl;
	
	d.push_front(6);
	d.push_front(5);
	d.push_front(4);

	for (int i : d)
		std::cout << i << " ";
	std::cout << std::endl;

	try
	{
		std::deque<int>::iterator it_d = easyfind(d, 5);
		std::cout << "Found in deque: " << *it_d << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Deque: " << e.what() << std::endl;
	}

	std::cout << "=== LIST TESTS ===" << std::endl;
	
	l.push_back(7);
	l.push_back(8);
	l.push_back(9);

	for (int i : l)
		std::cout << i << " ";
	std::cout << std::endl;

	try
	{
		std::list<int>::iterator it_l = easyfind(l, 8);
		std::cout << "Found in list: " << *it_l << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "List: " << e.what() << std::endl;
	}
	
	return (0);
}