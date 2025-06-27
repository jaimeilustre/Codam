/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Fixed.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/20 14:19:31 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/26 08:41:04 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <iostream>

#include "Fixed.hpp"

/*Default constructor*/
Fixed::Fixed(): _fixedPointNumber(0)
{
	std::cout << "Default constructor called" << std::endl;
}

/*Int constructor: Converts it to the corresponding fixed-point value*/
Fixed::Fixed(const int intValue)
{
	std::cout << "Int constructor called" << std::endl;
	_fixedPointNumber = intValue << _fractionalBits;
}

/*Float constructor: Converts it to the corresponding fixed-point value*/
Fixed::Fixed(const float floatValue)
{
	std::cout << "Float constructor called" << std::endl;
	_fixedPointNumber = roundf(floatValue * (1 << _fractionalBits));
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

/*Destructor*/
Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

/*Returns raw value of the fixed-point value*/
int Fixed::getRawBits(void) const
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

/*Overload of the insertion operator that inserts a floating-point representation of the fixed-point number into the output stream object passed as a parameter*/
std::ostream&	operator<<(std::ostream& os, const Fixed& fixed)
{
	os << fixed.toFloat();
	return (os);
}

/*Converts the fixed-point value to a floating-point value*/
float	Fixed::toFloat(void) const
{
	return (static_cast<float>(_fixedPointNumber)/ (1 << _fractionalBits));
}

/*Converts the fixed-point value to an integer value*/
int	Fixed::toInt(void) const
{
	return (_fixedPointNumber >> _fractionalBits);
}

/*Fixed arithmetic + operator*/
Fixed	Fixed::operator+(const Fixed& other) const
{
	Fixed	result;
	
	result.setRawBits(this->_fixedPointNumber + other._fixedPointNumber);
	return (result);
}

/*Fixed arithmetic - operator*/
Fixed	Fixed::operator-(const Fixed& other) const
{
	Fixed	result;
	
	result.setRawBits(this->_fixedPointNumber - other._fixedPointNumber);
	return (result);
}

/*Fixed arithmetic * operator*/
Fixed	Fixed::operator*(const Fixed& other) const
{
	Fixed		result;
	long long	mult;
	
	mult = (this->_fixedPointNumber * other._fixedPointNumber);
	result.setRawBits(mult >> _fractionalBits);
	return (result);
}

/*Fixed arithmetic / operator*/
Fixed	Fixed::operator/(const Fixed& other) const
{
	Fixed		result;
	long long	numerator;
	
	numerator = (this->_fixedPointNumber << _fractionalBits);
	result.setRawBits(numerator / other._fixedPointNumber);
	return (result);
}

/*Comparison > operator*/
bool	Fixed::operator>(const Fixed& other) const
{
	return (this->_fixedPointNumber > other._fixedPointNumber);
}

/*Comparison < operator*/
bool	Fixed::operator<(const Fixed& other) const
{
	return (this->_fixedPointNumber < other._fixedPointNumber);
}

/*Comparison >= operator*/
bool	Fixed::operator>=(const Fixed& other) const
{
	return (this->_fixedPointNumber >= other._fixedPointNumber);
}

/*Comparison <= operator*/
bool	Fixed::operator<=(const Fixed& other) const
{
	return (this->_fixedPointNumber <= other._fixedPointNumber);
}

/*Comparison == operator*/
bool	Fixed::operator==(const Fixed& other) const
{
	return (this->_fixedPointNumber == other._fixedPointNumber);
}

/*Comparison != operator*/
bool	Fixed::operator!=(const Fixed& other) const
{
	return (this->_fixedPointNumber != other._fixedPointNumber);
}

/*PRE-increment operator*/
Fixed&	Fixed::operator++()
{
	this->_fixedPointNumber += 1;
	return (*this);
}

/*PRE-decrement operator*/
Fixed&	Fixed::operator--()
{
	this->_fixedPointNumber -= 1;
	return (*this);
}

/*POST-increment operator*/
Fixed	Fixed::operator++(int)
{
	Fixed	temp;
	
	temp = *this;
	this->_fixedPointNumber += 1;
	return (temp);	
}

/*POST-decrement operator*/
Fixed	Fixed::operator--(int)
{
	Fixed	temp;

	temp = *this;
	this->_fixedPointNumber -= 1;
	return (temp);
}

/*Min function with NON-CONST parameters*/
Fixed&	Fixed::min(Fixed& a, Fixed& b)
{
	return (a < b ? a : b);
}

/*Min function with CONST parameters*/
const Fixed&	Fixed::min(const Fixed& a, const Fixed& b)
{
	return (a < b ? a : b);
}

/*Max function with NON-CONST parameters*/
Fixed&	Fixed::max(Fixed& a, Fixed& b)
{
	return (a > b ? a : b);
}

/*Max function with CONST parameters*/
const Fixed&	Fixed::max(const Fixed& a, const Fixed& b)
{
	return (a > b ? a : b);
}
