/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/12 10:57:17 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/10/24 15:43:26 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
	try
	{
		std::cout << "=== CREATING BUREAUCRATS ===" << std::endl;
		
		Bureaucrat	b1("John Doe", 139);
		Bureaucrat	b2("Jane Doe", 6);

		std::cout << b1 << std::endl;
		std::cout << b2 << std::endl;
		std::cout << std::endl;

		std::cout << "=== CREATING FORMS ===" << std::endl;
		
		Form		form1("first form", 140, 140);
		Form		form2("second form", 5, 5);

		std::cout << form1 << std::endl;
		std::cout << form2 << std::endl;
		std::cout << std::endl;

		std::cout << "=== SIGNING FORMS ===" << std::endl;
		
		try
		{
			b1.signForm(form1);
			std::cout << form1 << std::endl;
			b2.signForm(form2);
			std::cout << form2 << std::endl;
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
}
