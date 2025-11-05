/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   searchable_array_bag.hpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/05 13:28:39 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/05 14:20:24 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCHABLE_ARRAY_BAG_HPP
# define SEARCHABLE_ARRAY_BAG_HPP

# include "array_bag.hpp"
# include "searchable_bag.hpp"

class searchable_array_bag: public array_bag, public searchable_bag
{
	public:
		searchable_array_bag() {};
		searchable_array_bag(const searchable_array_bag& other): array_bag(other) {};
		searchable_array_bag&	operator=(const searchable_array_bag& other);
		
		bool	has(int value) const;
};

#endif