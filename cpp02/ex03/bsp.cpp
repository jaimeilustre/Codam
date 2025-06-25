/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bsp.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 07:33:39 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/25 07:39:36 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

bool	bsp( Point const a, Point const b, Point const c, Point const point)
{
    Point v0 = c - a;
    Point v1 = b - a;
    Point v2 = point - a;

    Fixed d00 = dot(v0, v0);
    Fixed d01 = dot(v0, v1);
    Fixed d11 = dot(v1, v1);
    Fixed d20 = dot(v2, v0);
    Fixed d21 = dot(v2, v1);

    Fixed denom = d00 * d11 - d01 * d01;
    Fixed v = (d11 * d20 - d01 * d21) / denom;
    Fixed w = (d00 * d21 - d01 * d20) / denom;
    Fixed u = Fixed(1) - v - w;

    return (u >= 0 && v >= 0 && w >= 0);
}
