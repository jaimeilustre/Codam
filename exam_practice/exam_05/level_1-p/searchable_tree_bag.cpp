/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   searchable_tree_bag.cpp                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/05 13:46:50 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/05 13:54:53 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_tree_bag.hpp"

searchable_tree_bag&	searchable_tree_bag::operator=(const searchable_tree_bag& other)
{
	if (this != &other)
		tree_bag::operator=(other);
	return (*this);
}

bool	searchable_tree_bag::has(int value) const
{
	node	*tmp = tree;

	while (tmp)
	{
		if (value == tmp->value)
			return (true);
		else if (value < tmp->value)
			tmp = tmp->l;
		else
			tmp = tmp->r;
	}
	return (false);
}

