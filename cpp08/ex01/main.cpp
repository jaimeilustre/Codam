/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 18:50:08 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/12/11 20:39:14 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>

int main(void)
{
	std::cout << "=== DEFAULT TESTS FROM SUBJECT ===" << std::endl;
	
	Span	sp = Span(5);
	
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	std::cout << "=== ADDING MULTIPLE NUMBERS TEST ===" << std::endl;

	Span				largeSp = Span(10000);
	std::vector<int>	v;

	for (int i = 0; i < 10000; i++)
		v.push_back(i);
	
	largeSp.addRange(v.begin(), v.end());

	std::cout << largeSp.shortestSpan() << std::endl;
	std::cout << largeSp.longestSpan() << std::endl;
	
	return (0);
}
