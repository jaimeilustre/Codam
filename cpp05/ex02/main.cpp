/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/12 10:57:17 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/10/24 14:13:01 by jilustre      ########   odam.nl         */
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
		std::cout << "=== CREATING BUREAUCRATS ===" << std::endl;
		
		Bureaucrat	b1("John Doe", 139);
		Bureaucrat	b2("Jane Doe", 73);
		Bureaucrat	b3("Joe Doe", 1);
		
		std::cout << b1 << std::endl;
		std::cout << b2 << std::endl;
		std::cout << b3 << std::endl;
		std::cout << std::endl;

		std::cout << "=== CREATING FORMS ===" << std::endl;

		ShrubberyCreationForm	sForm("Form 1");
		RobotomyRequestForm		rForm("Form 2");
		PresidentialPardonForm	pForm("Form 3");

		std::cout << sForm << std::endl;
		std::cout << rForm << std::endl;
		std::cout << pForm << std::endl;
		std::cout << std::endl;

		std::cout << "=== SIGNING FORMS ===" << std::endl;
				
		try
		{
			b1.signForm(sForm);
			b2.signForm(rForm);
			b3.signForm(pForm);
		}
		catch(std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}

		std::cout << sForm << std::endl;
		std::cout << rForm << std::endl;
		std::cout << pForm << std::endl;
		std::cout << std::endl;

		std::cout << "=== EXECUTING FORMS ===" << std::endl;		

		try
		{
			b1.executeForm(sForm);
			b2.executeForm(rForm);
			b3.executeForm(pForm);
		}
		catch(std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		std::cout << std::endl;
		std::cout << "=== DESTRUCTION ===" << std::endl;
	}
	catch(std::exception& e)
	{
		std::cerr << "Constructor failed!: " << e.what() << std::endl;
	}	
	return (0);
}
