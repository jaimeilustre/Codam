/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/02 10:45:45 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2026/01/02 11:08:22 by jaimeilustr   ########   odam.nl         */
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

		




	
	
	std::cout << "After: ";
	for (size_t i = 0; i < vect.size(); ++i)
		std::cout << vect[i] << " ";
	std::cout << std::endl;
}
