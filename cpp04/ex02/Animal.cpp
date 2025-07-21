/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Animal.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 16:43:09 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/17 07:21:03 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(): type("Non existent animal")
{
	std::cout << "Animal default constructor called!\n" << std::endl;
}

Animal::Animal(const Animal& other): type(other.type)
{
	std::cout << "Animal copy constructor called!\n" << std::endl;
}

Animal&	Animal::operator=(const Animal& other)
{
	std::cout << "Animal copy assignment operator called!\n" << std::endl;
	if (this != &other)
		type = other.type;
	return (*this);
}

Animal::~Animal()
{
	std::cout << "Animal destructor called!\n" << std::endl;
}

std::string	Animal::getType() const
{
	return (type);
}

void	Animal::makeSound() const
{
	std::cout << "Generic animal sound...\n" << std::endl;
}