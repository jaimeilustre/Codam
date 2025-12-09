/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Array.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 21:39:17 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/12/09 22:05:29 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>
# include <exception>

template <typename T> class Array
{
	private:
		T*				_arr;
		unsigned int	_size;

	public:
		// Orthodox canonical form
		Array();
		Array(unsigned int size);
		Array(const Array& other);
		Array&	operator=(const Array& other);
		~Array();

		// Element access
		T&			operator[](unsigned int index);
		const T&	operator[](unsigned int index) const;

		// Getter
		unsigned int	getSize() const;
};

# include "Array.tpp"

#endif