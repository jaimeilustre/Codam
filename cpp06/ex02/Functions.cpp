/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Functions.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/02 12:09:16 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/02 14:19:19 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>
#include <iostream>

Base*	generate(void)
{
	int randNb = rand() % 3;

	switch (randNb)
	{
		case 0:
			return (new A());
		case 1:
			return (new B());
		default:
			return (new C());
	}
}

void	identify(Base *p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown" << std::endl;
}

void	identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	std::cout << "Unknown" << std::endl;
}