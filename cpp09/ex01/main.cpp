/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 14:16:38 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2026/03/09 12:17:54 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Too few arguments" << std::endl;
		return (1);
	}
	try
	{
		int result = RPN::calculate(argv[1]);
		std::cout << result << std::endl;
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	return (0);
}