/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Point.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/24 14:54:16 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/25 07:39:54 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Fixed.hpp"
#include "Point.hpp"

/*Default constructor for point class*/
Point::Point(): x(0), y(0)
{
	// std::cout << "Default constructor called" << std::endl;
}

/*Parameterized constructor for point class*/
Point::Point(const Fixed& x, const Fixed& y): x(x), y(y)
{
	// std::cout << "Parameterized constructor called" << std::endl;
}

/*Destructor*/
Point::~Point()
{
	// std::cout << "Destructor called" << std::endl;
}

/*Copy constructor*/
Point::Point(const Point& other): x(other.x), y(other.y)
{
	// std::cout << "Copy constructor called" << std::endl;
}

/*Getter for x attribute*/
Fixed Point::getX() const
{
	return (x);
}

/*Getter for y attrinute*/
Fixed Point::getY() const
{
	return (y);
}

/*Vector subtraction between two points*/
Point	operator-(const Point& a, const Point& b)
{
	return (Point(a.getX() - b.getX(), a.getY() - b.getY()));
}

/*Dot product calculation of two 2D vectors*/
Fixed dot(const Point& a, const Point& b)
{
    return (a.getX() * b.getX() + a.getY() * b.getY());
}
