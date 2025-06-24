/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Point.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/24 14:54:16 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/24 15:42:17 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Fixed.hpp"
#include "Point.hpp"

/*Default constructor for point class*/
Point::Point(): x(0), y(0)
{
	std::cout << "Default constructor called" << std::endl;
}

/*Parameterized constructor for point class*/
Point::Point(const float x, const float y): x(x), y(y)
{
	std::cout << "Parameterized constructor called" << std::endl;
}

/*Destructor*/
Point::~Point()
{
	std::cout << "Destructor called" << std::endl;
}

/*Copy constructor*/
Point::Point(const Point& other): x(other.x), y(other.y)
{
	std::cout << "Copy constructor called" << std::endl;
}

/*Copy assignment operator*/
Point& Point::operator=(const Point& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
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


