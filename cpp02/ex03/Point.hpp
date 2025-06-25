/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Point.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/24 12:59:49 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/25 17:33:11 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

#include "Fixed.hpp"

class Point
{
	public:
		Point();
		Point(const Fixed& x, const Fixed& y);
		Point(const Point& other);
		Point& operator=(const Point& other) = delete;
		~Point();

		Fixed getX() const;
		Fixed getY() const;
	private:
		const Fixed x;
		const Fixed y;
};

Point	operator-(const Point& a, const Point& b);
Fixed	dot(const Point& a, const Point& b);
bool	bsp(Point const a, Point const b, Point const c, Point const point);

#endif
