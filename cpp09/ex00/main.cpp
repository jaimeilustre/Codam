/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/24 11:55:31 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/12/24 17:16:57 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file" << std::endl;
		return (1);
	}
	
	BitcoinExchange	btc;
	btc.loadDb("data.csv");
	btc.processFile(argv[1]);

	return (0);
}
