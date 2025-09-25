/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PresidentialPardonForm.cpp                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/04 11:04:00 by jilustre      #+#    #+#                 */
/*   Updated: 2025/09/25 13:57:49 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string& target): AForm("Presidential Pardon", 25, 5), _target(target)
{
	std::cout << "PresidentialPardonForm constructor called!\n" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other): AForm(other), _target(other._target)
{
	std::cout << "PresidentialPardonForm copy constructor called!\n" << std::endl;
}

PresidentialPardonForm&	PresidentialPardonForm::operator=(const PresidentialPardonForm& other)
{
	std::cout << "PresdientialPardonForm copy assignment operator called!\n" << std::endl;
	if (this != &other)
		_target = other._target;
	return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << "PresidentialPardonForm destructor called!\n" << std::endl;
}

void	PresidentialPardonForm::execute(Bureaucrat const& executor) const
{
	if (!getSignedBool())
		throw NotSignedException();
	if (executor.getGrade() > getGradeToExecute())
		throw GradeTooHighException();
	std::cout << _target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}
