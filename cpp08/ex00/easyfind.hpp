/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   easyfind.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 10:28:39 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/14 15:46:25 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <vector>
# include <deque>
# include <list>
# include <algorithm>
# include <stdexcept>

template <typename T> typename T::iterator easyfind(T& container, int val)
{
	typename T::iterator it = std::find(container.begin(), container.end(), val);

	if (it == container.end())
		throw std::runtime_error("Value not found");

	return (it);
}

#endif