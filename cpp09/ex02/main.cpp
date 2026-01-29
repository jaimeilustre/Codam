/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/29 09:19:19 by jilustre      #+#    #+#                 */
/*   Updated: 2026/01/29 09:19:51 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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
