/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RPN.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 10:41:49 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2026/03/09 12:18:01 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <sstream>
# include <stack>
# include <string>


class RPN
{
	private:
		RPN();
		RPN(const RPN& other);
		RPN&	operator=(const RPN& other) = delete;
		~RPN() = delete;

	public:
		static int calculate(const std::string& expression);
	
};

#endif