/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WrongAnimal.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/17 07:42:17 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/17 07:48:06 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(): type("Wrong Animal")
{
	std::cout << "Wrong animal default constructor called!\n" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other): type(other.type)
{
	std::cout << "Wrong animal copy constructor called!\n" << std::endl;
}

WrongAnimal&	WrongAnimal::operator=(const WrongAnimal& other)
{
	std::cout << "Wrong animal copy assignment operator called!\n" << std::endl;
	if (this != &other)
		type = other.type;
	return (*this);
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "Wrong animal destructor called!\n" << std::endl;
}

void	WrongAnimal::makeSound() const
{
	std::cout << "Wrong animal sound...\n" << std::endl;
}

std::string	WrongAnimal::getType() const
{
	return (type);
}
