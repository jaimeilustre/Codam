/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/12 10:57:17 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/10/22 15:01:43 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"                                                                                                    
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"

int main(void)
{
	try
	{
		std::cout << "=== BASIC BUREACRAT TESTS ===" << std::endl;
		
		Bureaucrat	b1("John Doe", 139);
		Bureaucrat	b2("Jane Doe", 6);
		Bureaucrat	b3("Joe Doe", 75);
		
		std::cout << b1 << std::endl;
		std::cout << b2 << std::endl;
		std::cout << b3 << std::endl;

		
		try
		{
			
		}
		catch(std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}

		try
		{
			
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
