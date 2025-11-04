/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vect2.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 11:52:36 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/04 11:58:54 by jaimeilustr   ########   odam.nl         */
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
