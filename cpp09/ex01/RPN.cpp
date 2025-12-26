/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RPN.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 14:01:33 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/12/26 14:21:23 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	RPN::calculate(const std::string& expression)
{
	std::stack<int>	stack;
	std::istringstream iss(expression);
	std::string	token;

	while (iss >> token)
	{
		if (token.size() == 1 && std::isdigit(token[0]))
			stack.push(token[0] - '0');
		else if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (stack.size() < 2)
				throw std::runtime_error("Error");
			int b = stack.top();
			stack.pop();
			int a = stack.top();
			stack.pop();
			
			switch (token[0])
			{
				case '+':
					stack.push(a + b);
					break ;
				case '-':
					stack.push(a - b);
					break ;
				case '*':
					stack.push(a * b);
					break ;
				case '/':
					if (b == 0)
						throw std::runtime_error("Error");
					stack.push(a / b);
			}
		}
		else
			throw std::runtime_error("Error");
	}
	
	if (stack.size() != 1)
		throw std::runtime_error("Error");
	return (stack.top());
}
