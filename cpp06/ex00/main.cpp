/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/29 20:00:27 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/11/29 20:05:06 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Insufficent arguments!" << std::endl;
		return (1);
	}
	ScalarConverter::convert(argv[1]);
	return (0);
}