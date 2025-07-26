/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cure.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/26 16:31:34 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/07/26 16:37:53 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure(): AMateria("cure")
{
	std::cout << "Cure default constructor called!\n" << std::endl;
}

Cure::Cure(const Cure& other): AMateria(other)
{
	std::cout << "Cure copy constructor called!\n" << std::endl;
}

Cure&	Cure::operator=(const Cure& other)
{
	std::cout << "Cure copy assignment operator called!\n" << std::endl;
	if (this != &other)
		_type = other._type;
	return (*this);
}

Cure::~Cure()
{
	std::cout << "Cure destructor called!\n" << std::endl;
}

AMateria*	Cure::clone() const
{
	return new Cure(*this);
}

void	Cure::use(ICharacter& target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}