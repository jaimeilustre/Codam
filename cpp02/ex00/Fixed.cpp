/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Fixed.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/20 14:19:31 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/26 08:18:35 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Fixed.hpp"

/*Default constructor*/
Fixed::Fixed(): _fixedPointNumber(0)
{
	std::cout << "Default constructor called" << std::endl;
}

/*Copy constructor: initializes a new object as a copy of an existing object*/
Fixed::Fixed(const Fixed& other): _fixedPointNumber(other._fixedPointNumber)
{
	std::cout << "Copy constructor called" << std::endl;
}

/*Copy assignment operator: assigns the value of one object to another already existing object*/
Fixed&	Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		_fixedPointNumber = other._fixedPointNumber;
	return (*this);
}
/*Default constructor*/
Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

/*Returns raw value of the fixed-point value*/
int	Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (_fixedPointNumber);
}

/*Sets the raw value of the fixed-point value*/
void	Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	_fixedPointNumber = raw;
}
