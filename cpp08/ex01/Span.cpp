/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Span.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 17:15:13 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/14 10:45:33 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(unsigned int n): N(n)
{
	_integers.reserve(n);
}

Span::Span(const Span& other): N(other.N), _integers(other._integers) {}

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

int	Span::shortestSpan() const
{
	if (_integers.size() < 2)
		throw std::runtime_error("Span only contains 1 or less integer");

	std::vector<int>	sortedSpan = _integers;
	std::sort(sortedSpan.begin(), sortedSpan.end());

	int	minSpan = INT_MAX;

	for (size_t i = 0; i < sortedSpan.size() - 1; i++)
	{
		int span = sortedSpan[i + 1] - sortedSpan[i];
		if (span < minSpan)
			minSpan = span;
	}
	return (minSpan);
}

int Span::longestSpan() const
{
	if (_integers.size() < 2)
		throw std::runtime_error("Span only contains 1 or less integer");
		
	std::vector<int>	sortedSpan = _integers;
	std::sort(sortedSpan.begin(), sortedSpan.end());

	int maxSpan = sortedSpan.back() - sortedSpan.front();

	return (maxSpan);
}