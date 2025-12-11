/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Span.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 17:15:13 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/11 17:23:04 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(unsigned int n): N(n)
{
	_integers.reserve(n);
}

Span::Span(const Span& other): N(other.N)
{
	*this = other;
}

Span&	Span::operator=(const Span& other)
{
	if (this != &other)
	{
		N = other.N;
		_integers = other._integers;
	}
	return (*this);
}

Span::~Span() {}

void	Span::addNumber(int n)
{
	if (_integers.size() >= N)
		throw std::runtime_error("Span is full");
	_integers.push_back(n);
}