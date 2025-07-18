/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WrongCat.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/17 07:50:21 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/17 07:53:09 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat()
{
	std::cout << "Wrong cat default constructor called!\n" << std::endl;
	type = "Wrong cat";
}

WrongCat::WrongCat(const WrongCat& other)
{
	std::cout << "Wrong cat copy constructor called!\n" << std::endl;
	type = other.type;
}

WrongCat&	WrongCat::operator=(const WrongCat& other)
{
	std::cout << "Wrong cat copy assignment operator called!\n" << std::endl;
	if (this != &other)
		type = other.type;
	return (*this);
}

WrongCat::~WrongCat()
{
	std::cout << "Wrong cat destructor called!\n" << std::endl;
}

void	WrongCat::makeSound() const
{
	std::cout << "Wrong cat sound...\n" << std::endl;
}