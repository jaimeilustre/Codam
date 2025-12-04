/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/04 10:16:59 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/04 10:17:11 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Functions.hpp"

int main(void)
{
	std::srand(time(NULL));
	
	Base *b = generate();

	std::cout << "Identify Base*: ";
	identify(b);

	std::cout << "Identify Base&: ";
	identify(*b);

	delete b;
	
	return (0);
}