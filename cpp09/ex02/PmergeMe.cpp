/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/02 10:45:45 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2026/02/28 15:53:16 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cmath>

long long PmergeMe::comparisons = 0;

struct CountingLess
{
	bool operator()(int a, int b) const
	{
		++PmergeMe::comparisons;
		return a < b;
	}
};

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

static std::vector<std::size_t> jacobsthalOrder(std::size_t m)
{
	std::vector<std::size_t>	order;
	if (m <= 2)
	{
		if (m == 2)
			order.push_back(1);
		return (order);
	}


	std::vector<std::size_t>	J;
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

	if (std::find(order.begin(), order.end(), static_cast<std::size_t>(1)) == order.end())
		order.insert(order.begin(), 1);
	
	std::vector<std::size_t> unique;
	unique.reserve(order.size());
	for (std::size_t i = 0; i < order.size(); ++i)
	{
		if (std::find(unique.begin(), unique.end(), order[i]) == unique.end())
			unique.push_back(order[i]);
	}
	return unique;
}

template <typename Seq>
struct Pending
{
	int small;
	int bound;
};

template <typename Seq>
static void createPairs(const Seq& input,
						Seq& mainChain,
						Seq& pendSmalls,
						std::size_t& oddIndex,
						std::vector< Pending<Seq> >& pendPairs)
{
	(void)pendSmalls;

	oddIndex = static_cast<std::size_t>(-1);

	for (std::size_t i = 0; i + 1 < input.size(); i += 2)
	{
		int a = input[i];
		int b = input[i + 1];
		
		if (CountingLess()(b, a))
			std::swap(a, b);
		
		mainChain.push_back(b);
		pendPairs.push_back(Pending<Seq>{a, b});
	}
	if ((input.size() % 2) == 1)
		oddIndex = input.size() - 1;
}

template <typename Seq>
static void insertBounded(Seq& mainChain, const Pending<Seq>& p)
{
	CountingLess comp;
	
	typename Seq::iterator boundIt = std::lower_bound(mainChain.begin(), mainChain.end(), p.bound, comp);
	typename Seq::iterator pos = std::lower_bound(mainChain.begin(), boundIt, p.small, comp);
	
	mainChain.insert(pos, p.small);
}

template <typename Seq>
static void fordJohnsonSort(Seq& seq)
{
	if (seq.size() <= 1)
		return;
		
	Seq mainChain;
	Seq dummyPend;
	std::vector< Pending<Seq> > pendPairs;
	mainChain.clear();
	dummyPend.clear();
	pendPairs.clear();

	std::size_t oddIndex;
	createPairs(seq, mainChain, dummyPend, oddIndex, pendPairs);

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

	if (oddIndex != static_cast<std::size_t>(-1))
	{
		CountingLess comp;
		int odd = seq[oddIndex];
		typename Seq::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), odd, comp);
		mainChain.insert(pos, odd);
	}
	seq.swap(mainChain);
}

void	PmergeMe::fjSort(std::vector<int>& vect)
{
	comparisons = 0;
	fordJohnsonSort(vect);
}

void	PmergeMe::fjSort(std::deque<int>& deq)
{
	comparisons = 0;
	fordJohnsonSort(deq);
}

int	PmergeMe::parserInts(const char* s)
{
	char	*end;
	errno = 0;
	long	v = std::strtol(s, &end, 10);

	if (*end != '\0' || errno == ERANGE || v < 0 || v > INT_MAX)
		throw std::runtime_error("Error");

	return static_cast<int>(v);
}

// // Vector version
// void	PmergeMe::createPairs(const std::vector<int>& input, std::vector<int>& main, std::vector<int>& pend, int& odd)
// {
// 	size_t	i = 0;
// 	for (; i + 1 < input.size(); i += 2)
// 	{
// 		int a = input[i];
// 		int b = input[i + 1];
		
// 		if (a > b)
// 			std::swap(a, b);
		
// 		pend.push_back(a);
// 		main.push_back(b);
// 	}
// 	if (i < input.size())
// 		odd = input[i];
// }

// void	PmergeMe::insert(std::vector<int>& main, const std::vector<int>& pend)
// {
// 	for (size_t i = 0; i < pend.size(); ++i)
// 	{
// 		std::vector<int>::iterator pos = std::lower_bound(main.begin(), main.end(), pend[i]);
// 		main.insert(pos, pend[i]);
// 	}
// }

// void	PmergeMe::fjSort(std::vector<int>& vect)
// {
// 	if (vect.size() <= 1)
// 		return ;
	
// 	std::vector<int> main;
// 	std::vector<int> pend;
// 	int odd = -1;

// 	main.reserve((vect.size() + 1) / 2);
// 	pend.reserve(vect.size() / 2);

// 	createPairs(vect, main, pend, odd);
// 	fjSort(main);
// 	insert(main, pend);

// 	if (odd != -1)
// 	{
// 		std::vector<int>::iterator pos = std::lower_bound(main.begin(), main.end(), odd);
// 		main.insert(pos, odd);
// 	}
	
// 	vect.swap(main);
// }

// void	PmergeMe::sort(int argc, char **argv)
// {
// 	if (argc < 2)
// 		throw std::runtime_error("Error: Only 1 number has been provided");
	
// 	std::vector<int>	vect;
// 	std::deque<int>		deq;

// 	for (int i = 1; i < argc; ++i)
// 	{
// 		int nb = parserInts(argv[i]);
// 		vect.push_back(nb);
// 		deq.push_back(nb);
// 	}

// 	std::cout << "Before: ";
// 	for (size_t i = 0; i < vect.size(); ++i)
// 		std::cout << vect[i] << " ";
// 	std::cout << std::endl;

// 	// Vector version
// 	auto	vectStart = std::chrono::high_resolution_clock::now();
// 	fjSort(vect);
// 	auto	vectEnd = std::chrono::high_resolution_clock::now();

// 	// Deque version
// 	auto	deqStart = std::chrono::high_resolution_clock::now();
	
// 	auto	deqEnd = std::chrono::high_resolution_clock::now();

// 	std::cout << "After: ";
// 	for (size_t i = 0; i < vect.size(); ++i)
// 		std::cout << vect[i] << " ";
// 	std::cout << std::endl;

// 	double	vectTime = std::chrono::duration<double, std::micro>(vectEnd - vectStart).count();
// 	double	deqTime = std::chrono::duration<double, std::micro>(deqEnd - deqStart).count();

// 	std::cout << "Time to process a range of " << vect.size() << " elements with std::vector : " << vectTime << " us" << std::endl;
// 	std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " << deqTime << " us" << std::endl;
// }

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

	long long vectComparisons = PmergeMe::comparisons;

	// ================= DEQUE ==================
	auto deqStart = std::chrono::high_resolution_clock::now();
	fjSort(deq);
	auto deqEnd = std::chrono::high_resolution_clock::now();

	long long deqComparisons = PmergeMe::comparisons;

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


