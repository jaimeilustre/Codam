/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/02 09:33:30 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2026/03/09 16:39:05 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <algorithm>
# include <chrono>
# include <climits>
# include <cmath>
# include <deque>
# include <iostream>
# include <vector>

class PmergeMe
{
	private:
		int	parserInts(const char* s);
		
		struct pending
		{
			int	lowerBound;
			int	upperBound;
		};
	
		bool	less(int a, int b);
		std::vector<size_t> jacobsthalOrder(size_t m);
		
		// Vector
		void 	createPairs(const std::vector<int>& input,
						std::vector<int>& mainChain,
						std::vector<pending>& pendPairs,
						int& oddIndex);
		void 	insertBounded(std::vector<int>& mainChain, const pending& p);
		void	fordJohnsonSort(std::vector<int>& vect);
		void	fjSort(std::vector<int>& vect);
		
		// Deque
		void	createPairs(const std::deque<int>& input,
						std::deque<int>& mainChain,
						std::vector<pending>& pendPairs,
						int& oddIndex);
		void	insertBounded(std::deque<int>& mainChain, const pending& p);		
		void	fordJohnsonSort(std::deque<int>& deq);
		void	fjSort(std::deque<int>& deq);
		
		// DEBUG: total comparisons in last sort
		int 		maxComparisonsBound(int n);		
		long long	_comparisons;
				
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other) = delete;
		PmergeMe&	operator=(const PmergeMe& other) = delete;
		~PmergeMe();
		
		void	sort(int argc, char **argv);
	
};

#endif