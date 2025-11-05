/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   searchable_tree_bag.hpp                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/05 13:44:22 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/05 13:54:37 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCHABLE_TREE_BAG_HPP
# define SEARCHABLE_TREE_BAG_HPP

# include "tree_bag.hpp"

class searchable_tree_bag: public tree_bag
{
	public:
		searchable_tree_bag() {};
		searchable_tree_bag(const searchable_tree_bag& other): tree_bag(other) {};
		searchable_tree_bag&	operator=(const searchable_tree_bag& other);

		bool	has(int value) const;
};

#endif