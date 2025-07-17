/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Dog.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 20:54:59 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/07/16 20:58:09 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
	std::cout << "Dog default constructor called!" << std::endl;
}

Dog::Dog(const Dog& other)
{
	std::cout << "Dog copy constructor called!" << std::endl;
	type = other.type;
}

Dog&	Dog::operator=(const Dog& other)
{
	if (this != &other)
		type = other.type;
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog destructor called!" << std::endl;
}

void	Dog::makeSound() const
{
	std::cout << "Woof woof..." << std::endl;
}