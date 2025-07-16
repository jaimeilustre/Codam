/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Animal.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 16:43:09 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/16 17:11:15 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal()
{
	std::cout << "Animal default constructor called!" << std::endl;
	std::cout << std::endl;
}

Animal::Animal(const Animal& other): _type(other._type)
{
	std::cout << "Animal copy constructor called!" << std::endl;
	std::cout << std::endl;
}

Animal&	Animal::operator=(const Animal& other)
{
	std::cout << "Animal copy assignment operator called!" << std::endl;
	if (this != &other)
		_type = other._type;
	return (*this);
}

Animal::~Animal()
{
	std::cout << "Animal destructor called!" << std::endl;
	std::cout << std::endl;
}

void	Animal::setType(const std::string& type)
{
	_type = type;
}

std::string	Animal::getType() const
{
	return (_type);
}

void	Animal::makeSound() const
{
	std::cout << "Generic animal sound..." << std::endl;
}