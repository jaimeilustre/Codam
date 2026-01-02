/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/02 10:45:45 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2026/01/02 11:29:58 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	PmergeMe::parserInts(const char* s)
{
	char	*end;
	errno = 0;
	long	v = std::strtol(s, &end, 10);

	if (*end != '\0' || errno == ERANGE || v < 0 || v > INT_MAX)
		throw std::runtime_error("Error");

	return static_cast<int>(v);
}

void	PmergeMe::sort(int argc, char **argv)
{
	std::vector<int>	vect;
	std::deque<int>		deq;

	for (int i = 1; i < argc; ++i)
	{
		int nb = parserInts(argv[i]);
		vect.push_back(nb);
		deq.push_back(nb);
	}

	std::cout << "Before: ";
	for (size_t i = 0; i < vect.size(); ++i)
		std::cout << vect[i] << " ";
	std::cout << std::endl;

	// Vector version
	auto	vectStart = std::chrono::high_resolution_clock::now();
	
	auto	vectEnd = std::chrono::high_resolution_clock::now();

	// Deque version
	auto	deqStart = std::chrono::high_resolution_clock::now();
	
	auto	deqEnd = std::chrono::high_resolution_clock::now();

	std::cout << "After: ";
	for (size_t i = 0; i < vect.size(); ++i)
		std::cout << vect[i] << " ";
	std::cout << std::endl;

	double	vectTime = std::chrono::duration<double, std::micro>(vectEnd - vectStart).count();
	double	deqTime = std::chrono::duration<double, std::micro>(deqEnd - deqStart).count();

	std::cout << "Time to process a range of " << vect.size() << " elements with std::vector : " << vectTime << " us" << std::endl;
	std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " << deqTime << " us" << std::endl;
}
