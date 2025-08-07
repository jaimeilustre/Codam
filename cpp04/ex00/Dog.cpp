/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Dog.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 20:54:59 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/08/01 06:54:49 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
	std::cout << "Dog default constructor called!\n" << std::endl;
	type = "Dog";
}

Dog::Dog(const Dog& other)
{
	std::cout << "Dog copy constructor called!\n" << std::endl;
	type = other.type;
}

Dog&	Dog::operator=(const Dog& other)
{
	std::cout << "Dog copy assignment operator called!\n" << std::endl;
	if (this != &other)
		type = other.type;
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog destructor called!\n" << std::endl;
}

void	Dog::makeSound() const
{
	std::cout << "Woof woof...\n" << std::endl;
}