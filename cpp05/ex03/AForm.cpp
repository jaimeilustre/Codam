/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   AForm.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 11:06:44 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/10/20 14:05:49 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute): 
	_name(name), _signedForm(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	std::cout << "Form constructor called!" << std::endl;
	if (gradeToSign < MAX_GRADE || gradeToExecute < MAX_GRADE)
		throw GradeTooHighException();
	else if (gradeToSign > MIN_GRADE || gradeToExecute > MIN_GRADE)
		throw GradeTooLowException();
}

AForm::AForm(const AForm& other):
	_name(other._name), _signedForm(other._signedForm),
	_gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
	std::cout << "Form copy constructor called!" << std::endl;
}

AForm&	AForm::operator=(const AForm& other)
{
	std::cout << "Form copy assignment operator called!" << std::endl;
	if (this != &other)
		_signedForm = other._signedForm;
	return (*this);
}

AForm::~AForm()
{
	std::cout << "Form destructor called!\n" << std::endl;
}

const char*	AForm::GradeTooHighException::what() const throw()
{
	return ("Grade above max grade!");
}

const char*	AForm::GradeTooLowException::what() const throw()
{
	return ("Grade below min grade!");
}

const char* AForm::NotSignedException::what() const throw()
{
	return ("Form not signed!");
}

std::string const&	AForm::getName() const
{
	return (_name);
}

bool	AForm::getSignedBool() const
{
	return (_signedForm);
}

int	AForm::getGradeToSign() const
{
	return (_gradeToSign);
}

int AForm::getGradeToExecute() const
{
	return (_gradeToExecute);
}

void	AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() <= _gradeToSign)
		_signedForm = true;
	else
		throw GradeTooLowException();
}

std::ostream&	operator<<(std::ostream& os, const AForm& form)
{
	os << "Form: " << form.getName() 
		<< ", Grade to sign: " << form.getGradeToSign() 
		<< ", Grade to execute: " << form.getGradeToExecute()
		<< ", Signed? " << (form.getSignedBool() ? "Yes" : "No");
	return (os);
}
