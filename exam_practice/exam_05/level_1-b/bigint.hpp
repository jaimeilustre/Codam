/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bigint.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 15:48:06 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/04 16:16:09 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>

class bigint
{
	public:
		// Canonical form
		bigint();
		bigint(unsigned int nbr);
		bigint(const bigint& other);
		bigint&	operator=(const bigint& other);
		~bigint();

		// Arithmetic operators
		bigint	operator+(const bigint& other) const;
		bigint&	operator+=(const bigint& other);
		
		// Comparison operators
		bool	operator==(const bigint& other);
		bool	operator!=(const bigint& other);
		bool	operator<(const bigint& other);
		bool	operator<=(const bigint& other);
		bool	operator>(const bigint& other);
		bool	operator>=(const bigint& other);
		
		// Increment operators
		bigint&	operator++();
		bigint	operator++(int);

		// Shifts
		bigint	operator<<(unsigned int amount) const;
		bigint&	operator<<=(unsigned int amount);
		
		bigint&	operator>>=(const bigint& other);

		// Getter
		std::string	getBig() const;
		
	private:
		std::string	_big;
};

std::ostream&	operator<<(std::ostream& os, const bigint& other);

#endif