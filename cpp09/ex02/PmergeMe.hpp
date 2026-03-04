/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/02 09:33:30 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2026/03/04 16:32:48 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <iostream>
# include <chrono>
# include <algorithm>
# include <climits>

// template <typename Seq>
// struct Pending
// {
// 	int small;
// 	int bound;
// };

class PmergeMe
{
	private:	
		void	fjSort(std::vector<int>& vect);
		void	fjSort(std::deque<int>& deq);

		void	fordJohnsonSort(std::vector<int>& vect);
		// void	fordJohnsonSort(std::deque<int>& deq);

		struct pending
		{
			int	lowerBound;
			int	upperBound;
		};

		void createPairs(const std::vector<int>& input,
						std::vector<int>& mainChain,
						std::vector<pending>& pendPairs,
						int& oddIndex);
		
		// void createPairs(const std::deque<int>& input,
		// 				std::deque<int>& mainChain,
		// 				std::vector<pending>& pendPairs,
		// 				int& oddIndex);


		void insertBounded(std::vector<int>& mainChain, const pending& p);
		// void insertBounded(std::deque<int>& mainChain, const pending& p);

		std::vector<size_t> jacobsthalOrder(size_t m);

		bool	less(int a, int b);
		
		int maxComparisonsBound(int n);
		int	parserInts(const char* s);

		// DEBUG: total comparisons in last sort
		long long _comparisons;
				
	public:
		// static void	sort(int argc, char **argv);
		// static void	fjSort(std::vector<int>& vect);
		// static void	fjSort(std::deque<int>& deq);
		
		PmergeMe();
		~PmergeMe();
		
		void	sort(int argc, char **argv);
	
};

#endif