/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MutantStack.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/12 10:25:32 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/12/12 12:09:05 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>

template <typename T> class MutantStack : public std::stack<T>
{
	public:
		MutantStack();
		MutantStack(const MutantStack& other);
		MutantStack&	operator=(const MutantStack& other);
		~MutantStack();

		typedef typename std::stack<T>::container_type::iterator				iterator;
		typedef typename std::stack<T>::container_type::reverse_iterator		reverseIterator;
		typedef	typename std::stack<T>::container_type::const_iterator			constIterator;
		typedef typename std::stack<T>::container_type::const_reverse_iterator	constReverseIterator;

		iterator				begin();
		iterator				end();

		reverseIterator			rbegin();
		reverseIterator			rend();

		constIterator			cbegin();
		constIterator			cend();

		constReverseIterator	crbegin();
		constReverseIterator	crend();
};

# include "MutantStack.tpp"

#endif