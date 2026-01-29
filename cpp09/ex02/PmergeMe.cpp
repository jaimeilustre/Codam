/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/02 10:45:45 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2026/01/29 09:01:30 by jaimeilustr   ########   odam.nl         */
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

// Vector version
void	PmergeMe::createPairs(const std::vector<int>& input, std::vector<int>& main, std::vector<int>& pend, int& odd)
{
	size_t	i = 0;
	for (; i + 1 < input.size(); i += 2)
	{
		int a = input[i];
		int b = input[i + 1];
		
		if (a > b)
			std::swap(a, b);
		
		pend.push_back(a);
		main.push_back(b);
	}
	if (i < input.size())
		odd = input[i];
}

void	PmergeMe::insert(std::vector<int>& main, const std::vector<int>& pend)
{
	for (size_t i = 0; i < pend.size(); ++i)
	{
		std::vector<int>::iterator pos = std::lower_bound(main.begin(), main.end(), pend[i]);
		main.insert(pos, pend[i]);
	}
}

void	PmergeMe::fjSort(std::vector<int>& vect)
{
	if (vect.size() <= 1)
		return ;
	
	std::vector<int> main;
	std::vector<int> pend;
	int odd = -1;

	createPairs(vect, main, pend, odd);
	fjSort(main);
	insert(main, pend);

	if (odd != -1)
	{
		std::vector<int>::iterator pos = std::lower_bound(main.begin(), main.end(), odd);
		main.insert(pos, odd);
	}
	
	vect = main;
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
	fjSort(vect);
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

int main(int argc, char** argv)
{
	try
	{
		PmergeMe::sort(argc, argv);
	}
	catch (...)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	return 0;
}
