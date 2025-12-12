/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MutantStack.tpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/12 10:39:28 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/12/12 12:08:25 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_TPP
# define MUTANTSTACK_TPP

# include "MutantStack.hpp"

template <typename T> MutantStack<T>::MutantStack() : std::stack<T>() {}

template <typename T> MutantStack<T>::MutantStack(const MutantStack& other) : std::stack<T>(other) {}

template <typename T> MutantStack<T>&	MutantStack<T>::operator=(const MutantStack& other)
{
	if (this != &other)
		std::stack<T>::operator=(other);
	return (*this);
}

template <typename T> MutantStack<T>::~MutantStack() {}

#endif