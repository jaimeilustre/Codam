/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   searchable_array_bag.cpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/05 13:36:55 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/05 13:41:10 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_array_bag.hpp"

searchable_array_bag&	searchable_array_bag::operator=(const searchable_array_bag& other)
{
	if (this != &other)
		array_bag::operator=(other);
	return (*this);
}

bool	searchable_array_bag::has(int value) const
{
	for (int i = 0; i < size; ++i)
	{
		if (data[i] == value)
			return (true);
	}
	return (false);
}