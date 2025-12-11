/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Span.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 17:01:09 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/11 17:08:42 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <algorithm>
# include <stdexcept>

class Span
{
	private:
		unsigned int		N;
		std::vector<int>	_nbs;
	
	public:
		// Orthodox canonical form
		Span(unsigned int n);
		Span(const Span& other);
		Span&	operator=(const Span& other);
		~Span();

		void	addNumber(int n);
		int		shortestSpan() const;
		int		longestSpan() const;
};

#endif