/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/20 14:41:24 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/04 16:44:34 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Fixed.hpp"
#include "Point.hpp"

int	main(void)
{
	Point a(0.0f, 0.0f);
	Point b(6.0f, 0.0f);
	Point c(2.0f, 10.0f);
	
	Point p1(2.0f, 2.0f);
	Point p2(4.0f, 5.0f);
	
	std::cout << "p1 is inside triangle: " << bsp(a, b, c, p1) << std::endl;
	std::cout << "p2 is inside triangle: " << bsp(a, b, c, p2) << std::endl;
	
    return (0);
}

