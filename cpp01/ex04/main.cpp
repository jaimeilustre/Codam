/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/04 15:52:23 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/16 11:16:28 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Replacer.hpp"

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Insufficient/Too many arguments!" << std::endl;
		return (1);	
	}
	else
	{
		Replacer replacer(argv[1], argv[2], argv[3]);
		if (!replacer.process())
			return (1);
	}
	return (0);
}
