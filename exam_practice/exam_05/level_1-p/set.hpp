/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/05 14:04:38 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/05 14:17:59 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "searchable_bag.hpp"

class set
{
	public:
		set(searchable_bag& bag): _bag(bag) {};

		// tree functions
		bool	has(int value);
		void	insert(int value);
		void	insert(int *arr, int size);
		void	print() const;
		void	clear();

		// getter
		const searchable_bag&	get_bag() const;
		
	private:
		searchable_bag&	_bag;
	
};

#endif