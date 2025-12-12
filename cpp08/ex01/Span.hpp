/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Span.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 17:01:09 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/12 14:29:02 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <algorithm>
# include <stdexcept>
# include <climits>

class Span
{
	private:
		unsigned int		N;
		std::vector<int>	_integers;
	
	public:
		// Orthodox canonical form
		Span(unsigned int n);
		Span(const Span& other);
		Span&	operator=(const Span& other);
		~Span();

		void	addNumber(int n);
		int		shortestSpan() const;
		int		longestSpan() const;

		template <typename T> void addRange(T begin, T end)
		{
			if (_integers.size() + std::distance(begin, end) > N)
				throw std::runtime_error("Span is full");
			_integers.insert(_integers.end(), begin, end);
		}
};

#endif