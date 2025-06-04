/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/04 08:18:32 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/04 11:19:33 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Harl.hpp"

int main(int argc, char **argv)
{
	Harl	harl;
	int		level;

	if (argc != 2)
	{
		std::cerr << "Insufficient/Too many arguments!" << std::endl;
		return (1);
	}
	level = harl.getLevel(argv[1]);
	switch (level)
	{
		case 0:
			harl.complain("DEBUG");
		case 1:
			harl.complain("INFO");
		case 2:
			harl.complain("WARNING");
		case 3:
			harl.complain("ERROR");
			break ;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;	
	}
	return (0);
}
