/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/12 10:57:17 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/10/14 13:50:01 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"

int main(void)
{
	Intern		someRandomIntern;
	Bureaucrat	boss("Boss", 1);
	AForm*		form1;
	
	form1 = someRandomIntern.makeForm("Robotomy Request", "Bender");
	if (form1)
	{
		boss.signForm(*form1);
		boss.executeForm(*form1);
		delete form1;
	}
	return (0);
}
