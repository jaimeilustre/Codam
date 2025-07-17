/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cat.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 20:25:38 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/07/16 20:53:40 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
	std::cout << "Cat default constructor called!" << std::endl;
	type = "Cat";
}

Cat::Cat(const Cat& other)
{
	std::cout << "Cat copy constructor called!" << std::endl;
	type = other.type;
}

Cat& Cat::operator=(const Cat& other)
{
	if (this != &other)
		type = other.type;
	return (*this);
}

Cat::~Cat()
{
	std::cout << "Cat destructor called!" << std::endl;
}

void	Cat::makeSound() const
{
	std::cout << "Meowwwww..." << std::endl;
}