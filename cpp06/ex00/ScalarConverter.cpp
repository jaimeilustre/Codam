/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScalarConverter.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/30 11:12:21 by jilustre      #+#    #+#                 */
/*   Updated: 2025/11/28 17:10:05 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
	std::cout << "ScalarConverter parameterized constructor called!" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
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

// Printing functions

void	ScalarConverter::printChar(char c)
{
	std::cout << "char: '" << c << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

void	ScalarConverter::printInt(int n)
{
	if (n >= 32 && n <= 126)
		std::cout << "char: '" << static_cast<char>(n) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	
	std::cout << "int: " << n << std::endl;
	std::cout << "float: " << static_cast<float>(n) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(n) << ".0" << std::endl;
}

void	ScalarConverter::printFloat(float f)
{
	if (f < 0 || f > 127)
		std::cout << "char: impossible" << std::endl;
	else if (static_cast<int>(f) >= 32 && static_cast<int>(f) <= 126)
		std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	
	if (f < INT_MIN || f > INT_MAX)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(f) << std::endl;
	
	std::cout << "float: " << f << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(f) << ".0" << std::endl;
}

void	ScalarConverter::printDouble(double d)
{
	if (d < 0 || d > 127)
		std::cout << "char: impossible" << std::endl;
	else if (static_cast<int>(d) >= 32 && static_cast<int>(d) <= 126)
		std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	
	if (d < INT_MIN || d > INT_MAX)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(d) << std::endl;
	
	std::cout << "float: " << static_cast<float>(d) << ".0f" << std::endl;
	std::cout << "double: " << d << ".0" << std::endl;
}

// Detecting functions

bool	ScalarConverter::pseudoFloat(const std::string& literal)
{
	return (literal == "-inff" || literal == "+inff" || literal == "nanf");
}

bool	ScalarConverter::pseudoDouble(const std::string& literal)
{
	return (literal == "-inf" || literal == "+inf" || literal == "nan");
}

bool	ScalarConverter::isChar(const std::string& literal)
{
	return (literal.length() == 3 && literal[0] == '\''
			&& literal[2] == '\'' && isprint(literal[1]));
}

bool	ScalarConverter::isInt(const std::string& literal)
{
	int i = 0;
	
	if (i == literal.length())
		return (false);
	
	if (literal[i] == '+' || literal[i] == '-')
		i++;
	
	while (i < literal.length())
	{
		if (!isdigit(literal[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ScalarConverter::isFloat(const std::string& literal)
{
	if (literal[literal.length() - 1] != 'f')
		return (false);
	
	std::string	digits = literal.substr(0, literal.length() - 1);
	
	int i = 0;
	if (digits[i] == '+' || digits[i] == '-')
		i++;
	
	bool	dot = false;
	bool	digit = false;
		
	while (i < digits.length())
	{
		if (digits[i] == '.')
		{
			if (dot)
				return (false);
			dot = true;
		}
		else if (isdigit(digits[i]))
			digit = true;
		else
			return (false);
	}
	return (dot && digit);
}

bool	ScalarConverter::isDouble(const std::string& literal)
{
	int i = 0;
	if (literal[i] == '+' || literal[i] == '-')
		i++;
		
	bool	dot = false;
	bool	digit = false;

	while (i < literal.length())
	{
		if (literal[i] == '.')
		{
			if (dot)
				return (false);
			dot = true;
		}
		else if (isdigit(literal[i]))
			digit = true;
		else
			return (false);
	}
	return (dot && digit);
}



