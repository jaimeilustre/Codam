/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Intern.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/30 16:04:14 by jilustre      #+#    #+#                 */
/*   Updated: 2025/09/30 16:07:08 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern()
{
	std::cout << "Intern default constructor called!\n" << std::endl;
}

Intern::Intern(const Intern& other) {};

Intern&	Intern::operator=(const Intern& other) {};

Intern::~Intern()
{
	std::cout << "Intern destructor called!\n" << std::endl;
}
