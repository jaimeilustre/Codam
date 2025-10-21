/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/12 10:57:17 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/10/21 15:55:04 by jilustre      ########   odam.nl         */
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
		std::cout << std::endl;

		std::cout << "=== COPY CONSTRUCTOR AND COPY ASSIGNMENT OPERATOR TESTS ===" << std::endl;
		
		Bureaucrat	original("Original", 140);
		Bureaucrat	copy(original);

		std::cout << original << std::endl;
		std::cout << copy << std::endl;

		try
		{
			original.incrementGrade();
		}
		catch(std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		std::cout << "After increment: " << original << std::endl;
		std::cout << "After increment: " << copy << std::endl;

		try
		{
			copy.decrementGrade();
		}
		catch(std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		std::cout << "After decrement: " << original << std::endl;
		std::cout << "After decrement: " << copy << std::endl;
	}
	catch(std::exception& e)
	{
		std::cerr << "Constructor failed!: " << e.what() << std::endl;
	}
}
