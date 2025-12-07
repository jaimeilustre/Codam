/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   whatever.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/07 10:23:18 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/12/07 10:34:20 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

# include <iostream>

template <typename T> void swap(T& x, T& y)
{
	T	tmp;

	tmp = x;
	x = y;
	y = tmp;
}

template <typename T> T min(T x, T y)
{
	return (x < y) ? x : y; 
}

template <typename T> T max(T x, T y)
{
	return (x > y) ? x : y;
}

#endif