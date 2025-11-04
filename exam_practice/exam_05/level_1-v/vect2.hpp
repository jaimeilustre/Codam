/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vect2.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 11:07:16 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/04 13:51:13 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
# define VECT2_HPP

# include <iostream>

class vect2
{
	public:
		// Canonical Form
		vect2();
		vect2(int x, int y);
		vect2(const vect2& other);
		vect2&	operator=(const vect2& other);
		~vect2();

		// [] Accessors
		int		operator[](int index) const;
		int&	operator[](int index);

		// Arithmetic operators
		vect2	operator+(const vect2& other) const;
		vect2&	operator+=(const vect2& other);
		
		vect2	operator-(const vect2& other) const;
		vect2&	operator-=(const vect2& other);

		vect2	operator*(int scalar) const;
		vect2&	operator*=(int scalar);

		// Unary minus
		vect2	operator-() const;

		// Increment and Decrement operators
		vect2&	operator++(); // pre-increment(++x)
		vect2	operator++(int); // post-increment(x++)
		
		vect2&	operator--(); // pre-decrement(--x)
		vect2	operator--(int); // post-decrement(x--)

		// Comparison operator
		bool	operator==(const vect2& other) const;
		bool	operator!=(const vect2& other) const;

	private:
		int	_x;
		int	_y;
};

vect2	operator*(int scalar, const vect2& other);
std::ostream&	operator<<(std::ostream& os, const vect2& other);

#endif