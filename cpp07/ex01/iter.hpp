/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iter.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 15:11:25 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/09 15:14:21 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

# include <iostream>

template <typename T, typename F> void iter(T *arr, size_t len, F func)
{
	if (!arr)
		return ;
	for (size_t i = 0; i < len; i++)
		function(arr[i]);
}

#endif