/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MutantStack.tpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/12 10:39:28 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/12/13 21:23:28 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_TPP
# define MUTANTSTACK_TPP

template <typename T> MutantStack<T>::MutantStack() : std::stack<T>() {}
template <typename T> MutantStack<T>::MutantStack(const MutantStack& other) : std::stack<T>(other) {}
template <typename T> MutantStack<T>&	MutantStack<T>::operator=(const MutantStack& other)
{
	if (this != &other)
		std::stack<T>::operator=(other);
	return (*this);
}
template <typename T> MutantStack<T>::~MutantStack() {}

// Normal iterator
template <typename T> typename MutantStack<T>::iterator MutantStack<T>::begin()
{
	return (this->c.begin());
}

template <typename T> typename MutantStack<T>::iterator MutantStack<T>::end()
{
	return (this->c.end());
}

// Const normal iterator
template <typename T> typename MutantStack<T>::const_iterator MutantStack<T>::begin() const
{
	return (this->c.begin());
}

template <typename T> typename MutantStack<T>::const_iterator MutantStack<T>::end() const
{
	return (this->c.end());
}

// Reverse iterator
template <typename T> typename MutantStack<T>::reverse_iterator MutantStack<T>::rbegin()
{
	return (this->c.rbegin());
}

template <typename T> typename MutantStack<T>::reverse_iterator MutantStack<T>::rend()
{
	return (this->c.rend());
}

// Const reverse iterator
template <typename T> typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rbegin() const
{
	return (this->c.rbegin());
}

template <typename T> typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rend() const
{
	return (this->c.rend());
}

#endif