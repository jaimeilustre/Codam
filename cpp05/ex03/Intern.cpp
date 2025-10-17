/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Intern.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/30 16:04:14 by jilustre      #+#    #+#                 */
/*   Updated: 2025/10/17 11:54:25 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "AForm.hpp"

static AForm* createShrubbery(const std::string& target)
{
	return new ShrubberyCreationForm(target);
}

static AForm* createRobotomy(const std::string& target)
{
	return new RobotomyRequestForm(target);
}

static AForm* createPresidential(const std::string& target)
{
	return new PresidentialPardonForm(target);	
}

Intern::Intern()
{
	std::cout << "Intern default constructor called!\n" << std::endl;
}

// Intern::Intern(const Intern& other) {};

// Intern&	Intern::operator=(const Intern& other) {};

Intern::~Intern()
{
	std::cout << "Intern destructor called!\n" << std::endl;
}

AForm*	Intern::makeForm(const std::string& formName, const std::string& formTarget)
{
	std::string formNames[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
	
	AForm*	(*creators[3])(const std::string&) = {
		createShrubbery,
		createRobotomy,
		createPresidential,
	};
	
	for (int i = 0; i < 3; i++)
	{
		if (formName == formNames[i])
		{
			std::cout << "Intern creates " << formName << std::endl;
			return creators[i](formTarget);
		}
	}
	std::cout << "Intern couldn't find a form named " << formName << std::endl;
	return (NULL); 	
}
