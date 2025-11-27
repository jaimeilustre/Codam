/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScalarConverter.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/30 10:58:41 by jilustre      #+#    #+#                 */
/*   Updated: 2025/11/27 14:56:18 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <iostream>
# include <cstdlib>
# include <cctype>
# include <climits>
# include <limits>

class ScalarConverter
{
	public:
		static void	convert(const std::string& input);
		
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter&	operator=(const ScalarConverter& other);
		~ScalarConverter();
	
		static void printChar(char c);
		static void	printInt(int n);
		static void	printFloat(float f);
		static void printDouble(double d);
		
};

#endif