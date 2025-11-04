/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bigint.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 16:17:52 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/04 16:42:06 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

bigint::bigint(): _big("") {};

bigint::bigint(unsigned int nbr): _big(std::to_string(nbr)) {};

bigint::bigint(const bigint& other): _big(other._big) {};

bigint&	bigint::operator=(const bigint& other)
{
	if (this != &other)
		_big = other._big;
	return (*this);
}

bigint::~bigint() {};

// Arithmetic operators
bigint	bigint::operator+(const bigint& other) const
{
	bigint	result(*this);
	result += other;
	return (result);
}

bigint&	bigint::operator+=(const bigint& other)
{
	return (*this);
}

// Comparison operators
bool	bigint::operator==(const bigint& other)
{
	return (_big == other._big);
}

bool	bigint::operator!=(const bigint& other)
{
	return (_big != other._big);
}

// Increment operators
bigint&	bigint::operator++()
{
	bigint	dummy(1);
	*this += dummy;
	return (*this);
}

bigint	bigint::operator++(int)
{
	bigint	dummy(1);
	bigint	tmp(*this);
	*this += dummy;
	return (tmp);
}

// Shifts

std::string	bigint::getBig() const
{
	return (_big);
}

std::ostream&	operator<<(std::ostream& os, const bigint& other)
{
	os << other.getBig();
	return (os);
}

