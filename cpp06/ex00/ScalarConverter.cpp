/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScalarConverter.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/30 11:12:21 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/04 12:27:08 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) {(void)other;}
ScalarConverter&	ScalarConverter::operator=(const ScalarConverter& other) {(void)other; return (*this);}
ScalarConverter::~ScalarConverter() {}

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
	if (std::isnan(f))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
		return ;
	}
	if (f == std::numeric_limits<float>::infinity())
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
		return ;
	}
	if (f == -std::numeric_limits<float>::infinity())
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
		return ;
	}
	
	double	d = static_cast<double>(f);
	
	if (std::isnan(d) || d < 0 || d > 127)
		std::cout << "char: impossible" << std::endl;
	else if (static_cast<int>(d) >= 32 && static_cast<int>(d) <= 126)
		std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	
	if (std::isnan(d) || d < static_cast<double>(INT_MIN)
			|| d > static_cast<double>(INT_MAX))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(d) << std::endl;
	
	std::cout << "float: " << f;
	if (f == static_cast<int>(f))
		std::cout << ".0";
	std::cout << "f" << std::endl;

	std::cout << "double: " << d;
	if (d == static_cast<int>(d))
		std::cout << ".0";
	std::cout << std::endl;
}

void	ScalarConverter::printDouble(double d)
{
	if (std::isnan(d))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
		return ;
	}
	if (d == std::numeric_limits<double>::infinity())
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
		return ;
	}
	if (d == -std::numeric_limits<double>::infinity())
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
		return ;
	}
	
	if (std::isnan(d) || d < 0 || d > 127)
		std::cout << "char: impossible" << std::endl;
	else if (static_cast<int>(d) >= 32 && static_cast<int>(d) <= 126)
		std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	
	if (std::isnan(d) || d < INT_MIN || d > INT_MAX)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(d) << std::endl;
	
	float	f = static_cast<float>(d);
	
	std::cout << "float: " << f;
	if (f == static_cast<int>(f))
		std::cout << ".0";
	std::cout << "f" << std::endl;

	std::cout << "double: " << d;
	if (d == static_cast<int>(d))
		std::cout << ".0";
	std::cout << std::endl;
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
	return (literal.size() == 1 && std::isprint(literal[0]) && !std::isdigit(literal[0]));
}

bool	ScalarConverter::isInt(const std::string& literal)
{
	if (literal.empty())
		return (false);
	
	size_t i = 0;
	
	if (literal[i] == '+' || literal[i] == '-')
		i++;
	
	while (i < literal.length())
	{
		if (!std::isdigit(literal[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ScalarConverter::isFloat(const std::string& literal)
{
	static const std::regex r("^[+-]?((\\d+(\\.\\d*)?)|(\\.\\d+))([eE][+-]?\\d+)?f$");
	return (std::regex_match(literal, r));
}


bool	ScalarConverter::isDouble(const std::string& literal)
{
    static const std::regex r("^[+-]?((\\d+(\\.\\d*)?)|(\\.\\d+))([eE][+-]?\\d+)?$");
    return (std::regex_match(literal, r));
}

ScalarConverter::type	ScalarConverter::detectType(const std::string& literal)
{
	if (literal.empty())
		return (INVALID);
	if (pseudoFloat(literal))
		return (PSEUDO_FLOAT);
	if (pseudoDouble(literal))
		return (PSEUDO_DOUBLE);
	if (isChar(literal))
		return (CHAR);
	if (isInt(literal))
		return (INT);
	if (isFloat(literal))
		return (FLOAT);
	if (isDouble(literal))
		return (DOUBLE);
	return (INVALID);
}

void	ScalarConverter::convert(const std::string& literal)
{
	type	literalType = detectType(literal);

	switch (literalType)
	{
		case CHAR:
			printChar(literal[0]);
			break ;
		case INT:
		{
            long	val = std::strtol(literal.c_str(), NULL, 10);

            if (val < INT_MIN || val > INT_MAX)
            {
                std::cout << "char: impossible" << std::endl;
				std::cout << "int: impossible" << std::endl;
				std::cout << "float: impossible" << std::endl;
				std::cout << "double: impossible" << std::endl;
                return;
            }
            printInt(static_cast<int>(val));
            break;
        }	
		case FLOAT:
			printFloat(std::stof(literal));
			break ;
		case DOUBLE:
			printDouble(std::stod(literal));
			break ;
		case PSEUDO_FLOAT:
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: " << literal << std::endl;
			std::cout << "double: " << literal.substr(0, literal.size() - 1) << std::endl;
			break ;
		case PSEUDO_DOUBLE:
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: " << literal << "f" << std::endl;
			std::cout << "double: " << literal << std::endl;
			break ;
		default:
			std::cout << "Invalid literal" << std::endl;
	}
}



