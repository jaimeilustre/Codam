/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   AMateria.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/26 16:04:58 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/07/26 16:17:21 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria()
{
	std::cout << "AMateria default constructor called!\n" << std::endl;
}

AMateria::AMateria(std::string const& type): _type(type)
{
	std::cout << "AMateria constructor called!\n" << std::endl;
}

AMateria::AMateria(const AMateria& other): _type(other._type)
{
	std::cout << "AMateria copy constructor called!\n" << std::endl;
}

AMateria&	AMateria::operator=(const AMateria& other)
{
	std::cout << "AMateria copy assignment operator called\n" << std::endl;
	if (this != &other)
		_type = other._type;
	return (*this);
}

AMateria::~AMateria()
{
	std::cout << "AMateria destructor called!\n" << std::endl;
}

std::string const&	AMateria::getType() const
{
	return (_type);
}

void	AMateria::use(ICharacter& target)
{
	(void)target;
}


