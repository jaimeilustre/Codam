/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScalarConverter.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/30 10:58:41 by jilustre      #+#    #+#                 */
/*   Updated: 2025/10/30 11:16:47 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <iostream>

class ScalarConverter
{
	public:
		ScalarConverter(const std::string& input);
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter&	operator=(const ScalarConverter& other);
		~ScalarConverter();

		static void	convert(const std::string& input);
		
	private:
		const std::string&	_input;
	
};

#endif