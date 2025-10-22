/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/12 10:57:17 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/10/22 13:34:27 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main(void)
{
	try
	{
		std::cout << "=== BASIC BUREACRAT TESTS ===" << std::endl;
		
		Bureaucrat b1("John Doe", 2);
		Bureaucrat b2("Jane Doe", 149);

		std::cout << b1 << std::endl;
		std::cout << b2 << std::endl;

		b1.incrementGrade();
		std::cout << "b1 incremented grade: " << b1 << std::endl;

		try
		{
			b1.incrementGrade();
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}

		b2.decrementGrade();
		std::cout << "b2 decremented grade: " << b2 << std::endl;

		try
		{
			b2.decrementGrade();
		}
		catch(std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
	}
	catch(std::exception& e)
	{
		std::cerr << "Constructor failed!: " << e.what() << std::endl;
	}
}
