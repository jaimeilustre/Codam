/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vect2.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 11:52:36 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/04 13:51:33 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

vect2::vect2(): _x(0), _y(0) {};

vect2::vect2(int x, int y): _x(x), _y(y) {};

vect2::vect2(const vect2& other): _x(other._x), _y(other._y) {};

vect2&	vect2::operator=(const vect2& other)
{
	if (this != &other)
	{
		_x = other._x;
		_y = other._y;
	}
	return (*this);
}

vect2::~vect2() {};

// [] Accessors
int	vect2::operator[](int index) const
{
	return (index == 0 ? _x : _y);
}

int&	vect2::operator[](int index)
{
	return (index == 0 ? _x : _y);
}

// Artithmetic operators
vect2	vect2::operator+(const vect2& other) const
{
	vect2	result(*this);
	result._x += other._x;
	result._y += other._y;
	return (result);
}

vect2&	vect2::operator+=(const vect2& other)
{
	_x += other._x;
	_y += other._y;
	return (*this);
}

vect2	vect2::operator-(const vect2& other) const
{
	vect2	result(*this);
	result._x -= other._x;
	result._y -= other._y;
	return (result);
}

vect2&	vect2::operator-=(const vect2& other)
{
	_x -= other._x;
	_y -= other._y;
	return (*this);
}

vect2	vect2::operator*(int scalar) const
{
	vect2	result(*this);
	result._x *= scalar;
	result._y *= scalar;
	return (result);
}

vect2&	vect2::operator*=(int scalar)
{
	_x *= scalar;
	_y *= scalar;
	return (*this);
}

// Unary minus
vect2	vect2::operator-() const
{
	vect2	result(*this);
	result._x = -result._x;
	result._y = -result._y;
	return (result);
}
// Increment and Decrement operators
vect2&	vect2::operator++()
{
	_x++;
	_y++;
	return (*this);
}

vect2	vect2::operator++(int)
{
	vect2	tmp(*this);
	_x++;
	_y++;
	return (tmp);	
}

vect2&	vect2::operator--()
{
	_x--;
	_y--;
	return (*this);
}

vect2	vect2::operator--(int)
{
	vect2	tmp(*this);
	_x--;
	_y--;
	return (tmp);
}

// Comparison operator
bool	vect2::operator==(const vect2& other) const
{
	return (_x == other._x && _y == other._y);
}

bool	vect2::operator!=(const vect2& other) const
{
	return (_x != other._x || _y != other._y);
}

vect2	operator*(int scalar, const vect2& other)
{
	vect2	result(other);
	result *= scalar;
	return (result);
}

std::ostream&	operator<<(std::ostream& os, const vect2& other)
{
	os << "{" << other[0] << ", " << other[1] << "}";
	return (os);
}

#include "vect2.hpp"

int main()
{
    vect2 v1; // 0, 0
    vect2 v2(1, 2); // 1, 2
    const vect2 v3(v2); // 1, 2
    vect2 v4 = v2; // 1, 2

    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v1: " << "{" << v1[0] << ", " << v1[1] << "}" << std::endl;
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "v3: " << v3 << std::endl;
    std::cout << "v4: " << v4 << std::endl;
    std::cout << v4++ << std::endl; // 2, 3
    std::cout << ++v4 << std::endl; // 3, 4
    std::cout << v4-- << std::endl; // 2, 3
    std::cout << --v4 << std::endl; // 1, 2
    v2 += v3; // 2, 4
    v1 -= v2; // -2, -4
    v2 = v3 + v3 *2; // 3, 6
    v2 = 3 * v2; // 9, 18
    v2 += v2 += v3; // 20, 40
    v1 *= 42; // -84, -168
    v1 = v1 - v1 +v1;
    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "-v2: " << -v2 << std::endl;
    std::cout << "v1[1]: " << v1[1] << std::endl;
    v1[1] = 12;
    std::cout << "v1[1]: " << v1[1] << std::endl;
    std::cout << "v3[1]: " << v3[1] << std::endl;
    std::cout << "v1 == v3: " << (v1 == v3) << std::endl;
    std::cout << "v1 == v1: " << (v1 == v1) << std::endl;
    std::cout << "v1 != v3: " << (v1 != v3) << std::endl;
    std::cout << "v1 != v1: " << (v1 != v1) << std::endl;
}
