/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Point.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/24 12:59:49 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/04 16:38:48 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

#include "Fixed.hpp"

class Point
{
	public:
		Point();
		Point(const float x, const float y);
		Point(const Point& other);
		Point&	operator=(const Point& other);
		~Point();

		Fixed	getX() const;
		Fixed	getY() const;
	private:
		const Fixed	_x;
		const Fixed	_y;
};

Point	operator-(const Point& a, const Point& b);
Fixed	dot(const Point& a, const Point& b);
bool	bsp(Point const a, Point const b, Point const c, Point const point);

#endif
