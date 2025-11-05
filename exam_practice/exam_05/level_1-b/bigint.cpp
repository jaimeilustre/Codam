/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bigint.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 16:17:52 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/05 11:06:29 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

bigint::bigint() {};

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
	int	carry = 0;
	int	i = _big.size() - 1;
	int j = other._big.size() - 1;
	std::string result;

	while (i >= 0 || j >= 0 || carry)
	{
		int x = i >= 0 ? _big[i] - '0' : 0;
		int y = j >= 0 ? other._big[i] - '0' : 0;
		int sum = x + y + carry;
		carry = sum / 10;
		result.push_back((sum % 10) + '0');
		--i;
		--j;
	}

	std::reverse(result.begin(), result.end());
	_big = result;	
	return (*this);
}

// Comparison operators
bool	bigint::operator==(const bigint& other) const
{
	return (_big == other._big);
}

bool	bigint::operator!=(const bigint& other) const
{
	return (_big != other._big);
}

bool	bigint::operator<(const bigint& other) const
{
	return (_big.size() != other._big.size())
		? _big.size() < other._big.size()
		: _big < other._big;
}

bool	bigint::operator<=(const bigint& other) const
{
	return !(*this > other);
}

bool	bigint::operator>(const bigint& other) const
{
	return (other < *this);
}

bool	bigint::operator>=(const bigint& other) const
{
	return !(*this < other);
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
bigint	bigint::operator<<(unsigned int amount) const
{
	bigint	result(*this);
	result <<= amount;
	return (result);
}

bigint&	bigint::operator<<=(unsigned int amount)
{
	if (_big != "0")
		_big.append(amount, '0');
	return (*this);
}

bigint&	bigint::operator>>=(const bigint& other)
{
	const unsigned int	size = _big.size();
	const unsigned long amount = std::atol(other._big.c_str());

	size >= amount ? _big.erase(size - amount) : _big = "0";
	return (*this);
}

std::string	bigint::getBig() const
{
	return (_big);
}

std::ostream&	operator<<(std::ostream& os, const bigint& other)
{
	os << other.getBig();
	return (os);
}

int main()
{
    const bigint a(42);
    bigint b(21), c, d(1337), e(d);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "(c += a) = " << (c += a) << std::endl;

    std::cout << "b = " << b << std::endl;
    std::cout << "++b = " << ++b << std::endl;
    std::cout << "b++ = " << b++ << std::endl;

    std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
    std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
    std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;

    std::cout << "a =" << a << std::endl;
    std::cout << "d =" << d << std::endl;

    std::cout << "(d < a) = " << (d < a) << std::endl;
    std::cout << "(d <= a) = " << (d <= a) << std::endl;
    std::cout << "(d > a) = " << (d > a) << std::endl;
    std::cout << "(d >= a) = " << (d >= a) << std::endl;
    std::cout << "(d == a) = " << (d == a) << std::endl;
    std::cout << "(d != a) = " << (d != a) << std::endl;
}

