/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Ice.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/26 16:20:54 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/08/01 06:56:54 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice(): AMateria("ice")
{
	std::cout << "Ice default constructor called!\n" << std::endl;
}

Ice::Ice(const Ice& other): AMateria(other)
{
	std::cout << "Ice copy constructor called!\n" << std::endl;
}

Ice&	Ice::operator=(const Ice& other)
{
	std::cout << "Ice copy assignment operator called!\n" << std::endl;
	if (this != &other)
		_type = other._type;
	return (*this);
}

Ice::~Ice()
{
	std::cout << "Ice destructor called!\n" << std::endl;
}

AMateria*	Ice::clone() const
{
	return new Ice(*this);
}

void	Ice::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
