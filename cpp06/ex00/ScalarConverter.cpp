/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScalarConverter.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/30 11:12:21 by jilustre      #+#    #+#                 */
/*   Updated: 2025/10/30 11:20:24 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(const std::string& input): _input(input)
{
	std::cout << "ScalarConverter parameterized constructor called!" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter& other): _input(other._input)
{
	std::cout << "ScalarConverter copy constructor called!" << std::endl;
}

ScalarConverter&	ScalarConverter::operator=(const ScalarConverter& other)
{
	(void)other;
	return (*this);
}

ScalarConverter::~ScalarConverter()
{
	std::cout << "ScalarConverter destructor called!" << std::endl;
}