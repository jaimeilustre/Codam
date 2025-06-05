/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/04 16:27:57 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/04 16:35:01 by jilustre      ########   odam.nl         */
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
	else
	{
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
	}
	return (0);
}
