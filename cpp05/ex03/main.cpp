/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/12 10:57:17 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/10/28 08:37:13 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

int main(void)
{
	std::cout << "=== CREATING INTERN ===" << std::endl; 
	
	Intern		someRandomIntern;

	std::cout << "=== CREATING BUREAUCRAT ===" << std::endl;
		
	Bureaucrat	boss("Boss", 1);
	
	std::cout << "=== SEEDING TIME FOR ROBOTOMY FORM ===" << std::endl << std::endl;
	
	std::srand(std::time(NULL));
	
	std::cout << "=== TESTING ROBOTOMY FORM ===" << std::endl;
	
	AForm*		form1;
	form1 = someRandomIntern.makeForm("robotomy request", "Bender");
	if (form1)
	{
		boss.signForm(*form1);
		boss.executeForm(*form1);
		delete form1;
	}

	std::cout << "=== TESTING PRESIDENTIAL PARDON FORM ===" << std::endl;
	
	AForm*	form2;
	form2 = someRandomIntern.makeForm("presidential pardon", "Prisoner");
	if (form2)
	{
		boss.signForm(*form2);
		boss.executeForm(*form2);
		delete form2;
	}

	std::cout << "=== TESTING SHRUBBERY CREATION FORM ===" << std::endl;

	AForm*	form3;
	form3 = someRandomIntern.makeForm("shrubbery creation", "Person");
	if (form3)
	{
		boss.signForm(*form3);
		boss.executeForm(*form3);
		delete form3;
	}

	std::cout << "=== TESTING NON-EXISTENT FORM ===" << std::endl;

	AForm*	form4;
	form4 = someRandomIntern.makeForm("non-existent", "ghost");
	if (form4)
	{
		boss.signForm(*form4);
		boss.executeForm(*form4);
		delete form4;
	}
	std::cout << std::endl;
	std::cout << "=== DESTRUCTION ===" << std::endl;
	return (0);
}
