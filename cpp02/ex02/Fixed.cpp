/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Fixed.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/20 14:19:31 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/24 11:43:32 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <iostream>

#include "Fixed.hpp"

/*Default constructor*/
Fixed::Fixed(): fixedPointNumber(0)
{
	std::cout << "Default constructor called" << std::endl;
}

/*Int parameterized constructor*/
Fixed::Fixed(const int intValue)
{
	std::cout << "Int constructor called" << std::endl;
	fixedPointNumber = intValue << fractionalBits;
}

/*Float parameterized constructor*/
Fixed::Fixed(const float floatValue)
{
	std::cout << "Float constructor called" << std::endl;
	fixedPointNumber = roundf(floatValue * (1 << fractionalBits));
}

/*Copy constructor*/
Fixed::Fixed(const Fixed& other): fixedPointNumber(other.fixedPointNumber)
{
	std::cout << "Copy constructor called" << std::endl;
}

/*Copy assignment operator*/
Fixed& Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		fixedPointNumber = other.fixedPointNumber;
	return (*this);
}

/*Destructor*/
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

/*Overload of the insertion operator*/
std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
	os << fixed.toFloat();
	return (os);
}

/*Conversion fixed to float*/
float Fixed::toFloat(void) const
{
	return (static_cast<float>(fixedPointNumber)/ (1 << fractionalBits));
}

/*Conversion fixed to int*/
int	Fixed::toInt(void) const
{
	return (fixedPointNumber >> fractionalBits);
}

/*Fixed arithmetic + operator*/
Fixed	Fixed::operator+(const Fixed& other) const
{
	Fixed	result;
	result.setRawBits(this->fixedPointNumber + other.fixedPointNumber);
	return (result);
}

/*Fixed arithmetic - operator*/
Fixed	Fixed::operator-(const Fixed& other) const
{
	Fixed	result;
	result.setRawBits(this->fixedPointNumber - other.fixedPointNumber);
	return (result);
}

/*Fixed arithmetic * operator*/
Fixed	Fixed::operator*(const Fixed& other) const
{
	Fixed	result;
	long long	mult;
	mult = (this->fixedPointNumber * other.fixedPointNumber);
	result.setRawBits(mult >> fractionalBits);
	return (result);
}

/*Fixed arithmetic / operator*/
Fixed	Fixed::operator/(const Fixed& other) const
{
	Fixed	result;
	long long	numerator;
	numerator = (this->fixedPointNumber << fractionalBits);
	result.setRawBits(numerator / other.fixedPointNumber);
	return (result);
}

/*Comparison > operator*/
bool	Fixed::operator>(const Fixed& other) const
{
	return (this->fixedPointNumber > other.fixedPointNumber);
}

/*Comparison < operator*/
bool	Fixed::operator<(const Fixed& other) const
{
	return (this->fixedPointNumber < other.fixedPointNumber);
}

/*Comparison >= operator*/
bool	Fixed::operator>=(const Fixed& other) const
{
	return (this->fixedPointNumber >= other.fixedPointNumber);
}

/*Comparison <= operator*/
bool	Fixed::operator<=(const Fixed& other) const
{
	return (this->fixedPointNumber <= other.fixedPointNumber);
}

/*Comparison == operator*/
bool	Fixed::operator==(const Fixed& other) const
{
	return (this->fixedPointNumber == other.fixedPointNumber);
}

/*Comparison != operator*/
bool	Fixed::operator!=(const Fixed& other) const
{
	return (this->fixedPointNumber != other.fixedPointNumber);
}

/*PRE-increment operator*/
Fixed&	Fixed::operator++()
{
	this->fixedPointNumber += 1;
	return (*this);
}

/*PRE-decrement operator*/
Fixed&	Fixed::operator--()
{
	this->fixedPointNumber -= 1;
	return (*this);
}

/*POST-increment operator*/
Fixed	Fixed::operator++(int)
{
	Fixed	temp;
	
	temp = *this;
	this->fixedPointNumber += 1;
	return (temp);	
}

/*POST-decrement operator*/
Fixed	Fixed::operator--(int)
{
	Fixed	temp;

	temp = *this;
	this->fixedPointNumber -= 1;
	return (temp);
}

/*Min function with NON-CONST parameters*/
Fixed& Fixed::min(Fixed& a, Fixed& b)
{
	return (a < b ? a : b);
}

/*Min function with CONST parameters*/
const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
	return (a < b ? a : b);
}

/*Max function with NON-CONST parameters*/
Fixed& Fixed::max(Fixed& a, Fixed& b)
{
	return (a > b ? a : b);
}

/*Max function with CONST parameters*/
const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
	return (a > b ? a : b);
}
