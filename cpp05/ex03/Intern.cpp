/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Intern.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/30 16:04:14 by jilustre      #+#    #+#                 */
/*   Updated: 2025/10/20 14:08:20 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"

Intern::Intern()
{
	std::cout << "Intern default constructor called!\n" << std::endl;
}

Intern::Intern(const Intern& other)
{
	(void)other;
}

Intern&	Intern::operator=(const Intern& other)
{
	(void)other;
	return (*this);
}

Intern::~Intern()
{
	std::cout << "Intern destructor called!\n" << std::endl;
}

AForm*	Intern::createShrubbery(const std::string& target)
{
	return new ShrubberyCreationForm(target);
}

AForm*	Intern::createRobotomy(const std::string& target)
{
	return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidential(const std::string& target)
{
	return new PresidentialPardonForm(target);	
}

AForm*	Intern::makeForm(const std::string& formName, const std::string& formTarget)
{
	std::string formNames[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
	
	AForm*	(Intern::*createForms[3])(const std::string&) = {
		&Intern::createShrubbery,
		&Intern::createRobotomy,
		&Intern::createPresidential,
	};
	
	for (int i = 0; i < 3; i++)
	{
		if (formName == formNames[i])
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (this->*createForms[i])(formTarget);
		}
	}
	std::cout << "Intern couldn't find a form named " << formName << std::endl << std::endl;
	return (NULL); 	
}
