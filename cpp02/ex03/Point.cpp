/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Point.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/24 14:54:16 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/26 10:32:03 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Fixed.hpp"
#include "Point.hpp"

/*Default constructor for point class*/
Point::Point(): _x(0), _y(0)
{
	// std::cout << "Default constructor called" << std::endl;
}

/*Parameterized constructor for point class*/
Point::Point(const Fixed& x, const Fixed& y):_x(x), _y(y)
{
	// std::cout << "Parameterized constructor called" << std::endl;
}

/*Destructor*/
Point::~Point()
{
	// std::cout << "Destructor called" << std::endl;
}

/*Copy constructor*/
Point::Point(const Point& other): _x(other._x), _y(other._y)
{
	// std::cout << "Copy constructor called" << std::endl;
}

/*Copy assignment operator: NOT IN USE here since both _x and _y are const and cannot be modified further after initialization*/
Point&	Point::operator=(const Point& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	// if (this != &other)
	// {
	// 	_x = other._x;
	// 	_y = other._y;
	// }
	return (*this);
}

/*Getter for x attribute*/
Fixed	Point::getX() const
{
	return (_x);
}

/*Getter for y attrinute*/
Fixed	Point::getY() const
{
	return (_y);
}

/*Vector subtraction between two points*/
Point	operator-(const Point& a, const Point& b)
{
	return (Point(a.getX() - b.getX(), a.getY() - b.getY()));
}

/*Dot product calculation of two 2D vectors*/
Fixed	dot(const Point& a, const Point& b)
{
    return (a.getX() * b.getX() + a.getY() * b.getY());
}
