/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/02 09:33:30 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2026/02/28 15:53:20 by jilustre      ########   odam.nl         */
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

// class PmergeMe
// {
// 	private:
// 		// Parser
// 		static int	parserInts(const char* s);

// 		// Vector container functions
// 		static void	fjSort(std::vector<int>& vect);
// 		static void	createPairs(const std::vector<int>& input, std::vector<int>& main, std::vector<int>& pend, int& odd);
// 		static void	insert(std::vector<int>& main, const std::vector<int>& pend);

// 		// Deque container functions
// 		// static void	fjSort(std::deque<int>& deq);
// 		// static void	createPairs(const std::deque<int>& input, std::deque<int>& main, std::deque<int>& pend, int& odd);
// 		// static void	insert(std::deque<int>& main, const std::deque<int>& pend);
		
// 	public:
// 		static void	sort(int argc, char **argv);
	
// };

class PmergeMe
{
	private:
		// Parser
		static int	parserInts(const char* s);

		// Vector container functions
		// static void	fjSort(std::vector<int>& vect);
		// static void	createPairs(const std::vector<int>& input, std::vector<int>& main, std::vector<int>& pend, int& odd);
		// static void	insert(std::vector<int>& main, const std::vector<int>& pend);

		// Deque container functions
		// static void	fjSort(std::deque<int>& deq);
		// static void	createPairs(const std::deque<int>& input, std::deque<int>& main, std::deque<int>& pend, int& odd);
		// static void	insert(std::deque<int>& main, const std::deque<int>& pend);
		
	public:
		// static void	sort(int argc, char **argv);
		static void	fjSort(std::vector<int>& vect);
		static void	fjSort(std::deque<int>& deq);

		// DEBUG: total comparisons in last sort
		static long long comparisons;

		// DEBUG: theoretical bound from article
		static int maxComparisonsBound(int n);

		static void	sort(int argc, char **argv);
	
};

#endif