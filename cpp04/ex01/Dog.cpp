/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Dog.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 20:54:59 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/07/31 06:14:37 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
	std::cout << "Dog default constructor called!\n" << std::endl;
	type = "Dog";
	brain = new Brain();
}

Dog::Dog(const Dog& other)
{
	std::cout << "Dog copy constructor called!\n" << std::endl;
	type = other.type;
	brain = new Brain(*other.brain);
}

Dog&	Dog::operator=(const Dog& other)
{
	std::cout << "Dog copy assignment operator called!\n" << std::endl;
	if (this != &other)
	{
		delete brain;
		brain = new Brain(*other.brain);
		type = other.type;
	}
	return (*this);
}

Dog::~Dog()
{
	delete brain;
	std::cout << "Dog destructor called!\n" << std::endl;
}

void	Dog::makeSound() const
{
	std::cout << "Woof woof...\n" << std::endl;
}

void Dog::setIdea(const std::string& idea, int index)
{
    brain->setIdea(idea, index);
}

std::string Dog::getIdea(int index) const
{
    return brain->getIdea(index);
}