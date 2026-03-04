/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/02 10:45:45 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2026/03/04 16:56:07 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cmath>

PmergeMe::PmergeMe(): _comparisons(0) {}
PmergeMe::~PmergeMe() {}

bool	PmergeMe::less(int a, int b)
{
	++_comparisons;
	return a < b;
}

int	PmergeMe::maxComparisonsBound(int n)
{
	int sum = 0;
	for (int k = 1; k <= n; ++k)
	{
		double value = (3.0 / 4.0) * k;
		sum += static_cast<int>(std::ceil(std::log2(value)));
	}
	return sum;
}

std::vector<size_t> PmergeMe::jacobsthalOrder(size_t m)
{
	std::vector<std::size_t> order;
	
    if (m <= 2)
    {
        if (m == 2) order.push_back(1);
        return order;
    }

    std::vector<std::size_t> J;
    J.push_back(0);
    J.push_back(1);
    while (true)
    {
        std::size_t next = J[J.size() - 1] + 2 * J[J.size() - 2];
        if (next >= m)
            break;
        J.push_back(next);
    }

    std::size_t prev = 1;
    for (std::size_t idx = 2; idx < J.size(); ++idx)
    {
        std::size_t cur = J[idx];
        for (std::size_t k = cur; k > prev; --k)
            order.push_back(k);
        prev = cur;
    }

    for (std::size_t k = m - 1; k > prev; --k)
        order.push_back(k);

    // Ensure index 1 is present (sometimes blocks may skip it depending on m)
    if (std::find(order.begin(), order.end(), static_cast<std::size_t>(1)) == order.end())
        order.insert(order.begin(), 1);

    // Remove any accidental duplicates (safety)
    std::vector<std::size_t> unique;
    unique.reserve(order.size());
    for (std::size_t i = 0; i < order.size(); ++i)
    {
        if (std::find(unique.begin(), unique.end(), order[i]) == unique.end())
            unique.push_back(order[i]);
    }
    return unique;
}

// VECTOR FUNCTIONS
void PmergeMe::createPairs(const std::vector<int>& input,
						std::vector<int>& mainChain,
						std::vector<pending>& pendPairs,
						int& oddIndex)
{
	oddIndex = -1;

	for (std::size_t i = 0; i + 1 < input.size(); i += 2)
	{
		int a = input[i];
		int b = input[i + 1];
		
		if (less(b, a))
			std::swap(a, b);
		
		mainChain.push_back(b);
		pendPairs.push_back(pending{a, b});
	}
	if ((input.size() % 2) != 0)
		oddIndex = input.back();
}

void PmergeMe::insertBounded(std::vector<int>& mainChain, const pending& p)
{
	// Find bound
	std::vector<int>::iterator boundIt =
		std::lower_bound(mainChain.begin(),
						 mainChain.end(),
						 p.upperBound,
						 [this](int a, int b) { return less(a, b); });

	// Insert small up to bound
	std::vector<int>::iterator pos =
		std::lower_bound(mainChain.begin(),
						 boundIt,
						 p.lowerBound,
						 [this](int a, int b) { return less(a, b); });
	
	mainChain.insert(pos, p.lowerBound);
}

void	PmergeMe::fordJohnsonSort(std::vector<int>& vect)
{
	if (vect.size() <= 1)
		return;
		
	std::vector<int> mainChain;
	std::vector<pending> pendPairs;
	int oddIndex;
	
	createPairs(vect, mainChain, pendPairs, oddIndex);

	fordJohnsonSort(mainChain);
	
	if (!pendPairs.empty())
	{
		insertBounded(mainChain, pendPairs[0]);
		
		std::vector<std::size_t> order = jacobsthalOrder(pendPairs.size());
		
		for (std::size_t i = 0; i < order.size(); ++i)
		{
			std::size_t idx = order[i];
			if (idx < pendPairs.size())
				insertBounded(mainChain, pendPairs[idx]);
		}
	}

	if (oddIndex != -1)
	{
		std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), oddIndex, [this](int a, int b) { return less(a, b); });
		mainChain.insert(pos, oddIndex);
	}
	vect.swap(mainChain);
}

void	PmergeMe::fjSort(std::vector<int>& vect)
{
	_comparisons = 0;
	fordJohnsonSort(vect);
}

// DEQUE FUNCTIONS


// void	PmergeMe::fjSort(std::deque<int>& deq)
// {
// 	_comparisons = 0;
// 	fordJohnsonSort(deq);
// }

int	PmergeMe::parserInts(const char* s)
{
	char	*end;
	errno = 0;
	long	v = std::strtol(s, &end, 10);

	if (*end != '\0' || errno == ERANGE || v < 0 || v > INT_MAX)
		throw std::runtime_error("Error");

	return static_cast<int>(v);
}

void PmergeMe::sort(int argc, char **argv)
{
	if (argc < 2)
		throw std::runtime_error("Error");

	std::vector<int> vect;
	std::deque<int>  deq;

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

	// ================= VECTOR =================
	auto vectStart = std::chrono::high_resolution_clock::now();
	fjSort(vect);
	auto vectEnd = std::chrono::high_resolution_clock::now();

	long long vectComparisons = PmergeMe::_comparisons;

	// ================= DEQUE ==================
	auto deqStart = std::chrono::high_resolution_clock::now();
	// fjSort(deq);
	auto deqEnd = std::chrono::high_resolution_clock::now();

	long long deqComparisons = PmergeMe::_comparisons;

	// ==========================================

	std::cout << "After: ";
	for (size_t i = 0; i < vect.size(); ++i)
		std::cout << vect[i] << " ";
	std::cout << std::endl;

	double vectTime =
		std::chrono::duration<double, std::micro>(vectEnd - vectStart).count();

	double deqTime =
		std::chrono::duration<double, std::micro>(deqEnd - deqStart).count();

	std::cout << "Time to process a range of "
			  << vect.size()
			  << " elements with std::vector : "
			  << vectTime << " us"
			  << std::endl;

	std::cout << "Time to process a range of "
			  << deq.size()
			  << " elements with std::deque : "
			  << deqTime << " us"
			  << std::endl;


	int bound = maxComparisonsBound(static_cast<int>(vect.size()));

	std::cout << "Vector comparisons: " << vectComparisons << std::endl;
	std::cout << "Deque comparisons:  " << deqComparisons << std::endl;
	std::cout << "Theoretical bound:  " << bound << std::endl;
}


