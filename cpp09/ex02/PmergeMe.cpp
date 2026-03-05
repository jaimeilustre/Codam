/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/02 10:45:45 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2026/03/05 16:23:24 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(): _comparisons(0) {}
PmergeMe::~PmergeMe() {}

int	PmergeMe::parserInts(const char* s)
{
	char	*end;
	errno = 0;
	long	v = std::strtol(s, &end, 10);

	if (*end != '\0' || errno == ERANGE || v < 0 || v > INT_MAX)
		throw std::runtime_error("Error");

	return static_cast<int>(v);
}

bool	PmergeMe::less(int a, int b)
{
	++_comparisons;
	return a < b;
}

// Generates the insertion order for the pending elements using Jacobsthal numbers
std::vector<size_t> PmergeMe::jacobsthalOrder(size_t m)
{
	// Step 1: Create result container
	std::vector<std::size_t> order; // insertion order of indices
	
	
	// Step 2: For small cases since 0 or 1 elements requires no insertion
    if (m <= 2)
    {
        if (m == 2)
			order.push_back(1);
        return order;
    }

	// Step 3: Building Jacobsthal sequence
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

	// Step 4: Build insertion blocks
    std::size_t prev = 1; // Tracks previous Jacobsthal value
	
    for (std::size_t idx = 2; idx < J.size(); ++idx)
    {
        std::size_t cur = J[idx];
        for (std::size_t k = cur; k > prev; --k)
            order.push_back(k);
        prev = cur;
    }

	// Step 5: Finish remaining indices (if Jacobsthal didn't cover all indices)
    for (std::size_t k = m - 1; k > prev; --k)
        order.push_back(k);

    // Step 6: Ensure index 1 is present (sometimes blocks may skip it depending on m)
    if (std::find(order.begin(), order.end(), static_cast<std::size_t>(1)) == order.end())
        order.insert(order.begin(), 1);

    // Step 7: Remove duplicates (safety)
    std::vector<std::size_t> unique;
    unique.reserve(order.size());
    for (std::size_t i = 0; i < order.size(); ++i)
    {
        if (std::find(unique.begin(), unique.end(), order[i]) == unique.end())
            unique.push_back(order[i]);
    }
    return unique; // Returns safe insertion order
}

// VECTOR FUNCTIONS

// Creates larger values of each pair, stores both values, leftover element if size is odd
void PmergeMe::createPairs(const std::vector<int>& input,
						std::vector<int>& mainChain,
						std::vector<pending>& pendPairs,
						int& oddIndex)
{
	oddIndex = -1; // Initialize odd marker (no odd yet)

	// Pair elements: moving in steps of 2
	for (std::size_t i = 0; i + 1 < input.size(); i += 2)
	{
		int a = input[i];
		int b = input[i + 1];
		
		// Ensure a is smaller than b
		if (less(b, a))
			std::swap(a, b);
		
		mainChain.push_back(b); // Pushes larger elements
		pendPairs.push_back(pending{a, b}); // Stores pair
	}
	if ((input.size() % 2) != 0)
		oddIndex = input.back(); // If odd number, store last one
}

// Inserts the smaller element of a pair only up to its partner
void PmergeMe::insertBounded(std::vector<int>& mainChain, const pending& p)
{
	// Find upper bound: find position of the larger partner
	std::vector<int>::iterator boundIt =
		std::lower_bound(mainChain.begin(),
						 mainChain.end(),
						 p.upperBound,
						 [this](int a, int b) { return less(a, b); });

	// Find the correct position to insert smaller element
	std::vector<int>::iterator pos =
		std::lower_bound(mainChain.begin(),
						 boundIt,
						 p.lowerBound,
						 [this](int a, int b) { return less(a, b); });
	
	mainChain.insert(pos, p.lowerBound); // insert smaller element
}

// Main Ford Johnson algorithm
void	PmergeMe::fordJohnsonSort(std::vector<int>& vect)
{
	// Check if already sorted
	if (vect.size() <= 1)
		return;
	
	// Create structures
	std::vector<int> mainChain; 
	std::vector<pending> pendPairs;
	int oddIndex;
	
	// Split input into pairs
	createPairs(vect, mainChain, pendPairs, oddIndex);

	// Recursively sort mainChain
	fordJohnsonSort(mainChain);
	
	// Insert pending elements
	if (!pendPairs.empty())
	{
		insertBounded(mainChain, pendPairs[0]); // Insert first pair manually
		
		std::vector<std::size_t> order = jacobsthalOrder(pendPairs.size()); // Get optimal order
		
		// Insert remaining pending elements in Jacobsthal order
		for (std::size_t i = 0; i < order.size(); ++i)
		{
			std::size_t idx = order[i];
			if (idx < pendPairs.size())
				insertBounded(mainChain, pendPairs[idx]);
		}
	}

	// Insert odd element
	if (oddIndex != -1)
	{
		std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), oddIndex, [this](int a, int b) { return less(a, b); });
		mainChain.insert(pos, oddIndex);
	}
	
	vect.swap(mainChain); // Replace original vect with the sorted one
}

// FJ sort wrapper
void	PmergeMe::fjSort(std::vector<int>& vect)
{
	_comparisons = 0;
	fordJohnsonSort(vect);
}

// DEQUE FUNCTIONS
void PmergeMe::createPairs(const std::deque<int>& input,
						std::deque<int>& mainChain,
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

void PmergeMe::insertBounded(std::deque<int>& mainChain, const pending& p)
{
	// Find bound
	std::deque<int>::iterator boundIt =
		std::lower_bound(mainChain.begin(),
						 mainChain.end(),
						 p.upperBound,
						 [this](int a, int b) { return less(a, b); });

	// Insert small up to bound
	std::deque<int>::iterator pos =
		std::lower_bound(mainChain.begin(),
						 boundIt,
						 p.lowerBound,
						 [this](int a, int b) { return less(a, b); });
	
	mainChain.insert(pos, p.lowerBound);
}

void	PmergeMe::fordJohnsonSort(std::deque<int>& deq)
{
	if (deq.size() <= 1)
		return;
		
	std::deque<int> mainChain;
	std::vector<pending> pendPairs;
	int oddIndex;
	
	createPairs(deq, mainChain, pendPairs, oddIndex);

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
		std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), oddIndex, [this](int a, int b) { return less(a, b); });
		mainChain.insert(pos, oddIndex);
	}
	deq.swap(mainChain);
}

void	PmergeMe::fjSort(std::deque<int>& deq)
{
	_comparisons = 0;
	fordJohnsonSort(deq);
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
	fjSort(deq);
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


