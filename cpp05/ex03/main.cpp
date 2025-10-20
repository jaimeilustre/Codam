/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/12 10:57:17 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/10/20 14:08:38 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

int main(void)
{
	Intern		someRandomIntern;
	Bureaucrat	boss("Boss", 1);
	
	std::srand(std::time(NULL));
	
	AForm*		form1;
	form1 = someRandomIntern.makeForm("robotomy request", "Bender");
	if (form1)
	{
		boss.signForm(*form1);
		boss.executeForm(*form1);
		delete form1;
	}

	AForm*	form2;
	form2 = someRandomIntern.makeForm("presidential pardon", "Prisoner");
	if (form2)
	{
		boss.signForm(*form2);
		boss.executeForm(*form2);
		delete form2;
	}

	AForm*	form3;
	form3 = someRandomIntern.makeForm("shrubbery creation", "Person");
	if (form3)
	{
		boss.signForm(*form3);
		boss.executeForm(*form3);
		delete form3;
	}

	AForm*	form4;
	form4 = someRandomIntern.makeForm("non-existent", "ghost");
	if (form4)
	{
		boss.signForm(*form4);
		boss.executeForm(*form4);
		delete form4;
	}
	
	return (0);
}
