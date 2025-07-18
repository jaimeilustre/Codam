/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cat.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 20:25:38 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/07/18 15:31:30 by jilustre      ########   odam.nl         */
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
		type = other.type;
		delete brain;
		brain = new Brain(*other.brain);
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