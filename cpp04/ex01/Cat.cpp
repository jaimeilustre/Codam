/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cat.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 20:25:38 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/07/31 06:14:51 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
	std::cout << "Cat default constructor called!\n" << std::endl;
	type = "Cat";
	brain = new Brain();
}

Cat::Cat(const Cat& other)
{
	std::cout << "Cat copy constructor called!\n" << std::endl;
	type = other.type;
	brain = new Brain(*other.brain);
}

Cat&	Cat::operator=(const Cat& other)
{
	std::cout << "Cat copy assignment operator called!\n" << std::endl;
	if (this != &other)
	{
		delete brain;
		brain = new Brain(*other.brain);
		type = other.type;
	}
	return (*this);
}

Cat::~Cat()
{
	delete brain;
	std::cout << "Cat destructor called!\n" << std::endl;
}

void	Cat::makeSound() const
{
	std::cout << "Meowwwww...\n" << std::endl;
}

void Cat::setIdea(const std::string& idea, int index)
{
    brain->setIdea(idea, index);
}

std::string Cat::getIdea(int index) const
{
    return brain->getIdea(index);
}