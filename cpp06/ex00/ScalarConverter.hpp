/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScalarConverter.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/30 10:58:41 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/01 16:26:02 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <iostream>
// # include <cstdlib>
// # include <cctype>
# include <cmath>
# include <climits>
# include <limits>

class ScalarConverter
{
	public:
		static void	convert(const std::string& literal);
		
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter&	operator=(const ScalarConverter& other);
		~ScalarConverter();
	
		enum type
		{
			CHAR,
			INT,
			FLOAT,
			DOUBLE,
			PSEUDO_FLOAT,
			PSEUDO_DOUBLE,
			INVALID,
		};

		static type	detectType(const std::string& literal);

		static void printChar(char c);
		static void	printInt(int n);
		static void	printFloat(float f);
		static void printDouble(double d);
		
		static bool	pseudoFloat(const std::string& literal);
		static bool	pseudoDouble(const std::string& literal);

		static bool	isChar(const std::string& literal);
		static bool isInt(const std::string& literal);
		static bool	isFloat(const std::string& literal);
		static bool isDouble(const std::string& literal);
};

#endif