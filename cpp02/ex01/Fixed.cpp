/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Fixed.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/20 14:19:31 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/20 18:36:10 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <iostream>

#include "Fixed.hpp"

Fixed::Fixed(): fixedPointNumber(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int intValue)
{
	std::cout << "Int constructor called" << std::endl;
	fixedPointNumber = intValue << fractionalBits;
}

Fixed::Fixed(const float floatValue)
{
	std::cout << "Float constructor called" << std::endl;
	fixedPointNumber = roundf(floatValue * (1 << fractionalBits));
}

Fixed::Fixed(const Fixed& other): fixedPointNumber(other.fixedPointNumber)
{
	std::cout << "Copy constructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		fixedPointNumber = other.fixedPointNumber;
	return (*this);
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (fixedPointNumber);
}

void Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	fixedPointNumber = raw;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
	os << fixed.toFloat();
	return (os);
}

float Fixed::toFloat(void) const
{
	return (static_cast<float>(fixedPointNumber)/ (1 << fractionalBits));
}

int	Fixed::toInt(void) const
{
	return (fixedPointNumber >> fractionalBits);
}
