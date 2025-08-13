/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Form.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 11:06:44 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/08/13 15:20:02 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute): 
	_name(name), _signedForm(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	std::cout << "Form constructor called!" << std::endl;
	if (gradeToSign < MAX_GRADE || gradeToExecute < MAX_GRADE)
		throw GradeTooHighException();
	else if (gradeToSign > MIN_GRADE || gradeToExecute > MIN_GRADE)
		throw GradeTooLowException();
}

Form::Form(const Form& other):
	_name(other._name), _signedForm(other._signedForm),
	_gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
	std::cout << "Form copy constructor called!" << std::endl;
}

Form&	Form::operator=(const Form& other)
{
	std::cout << "Form copy assignment operator called!" << std::endl;
	if (this != &other)
		_signedForm = other._signedForm;
	return (*this);
}

Form::~Form()
{
	std::cout << "Form destructor called!" << std::endl;
}

const char*	Form::GradeTooHighException::what() const throw()
{
	return ("Grade above max grade!");
}

const char*	Form::GradeTooLowException::what() const throw()
{
	return ("Grade below min grade!");
}

std::string const&	Form::getName() const
{
	return (_name);
}

bool	Form::getSignedBool() const
{
	return (_signedForm);
}

int	Form::getGradeToSign() const
{
	return (_gradeToSign);
}

int Form::getGradeToExecute() const
{
	return (_gradeToExecute);
}

void	Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() <= _gradeToSign)
		_signedForm = true;
	else
		throw GradeTooLowException();
}

std::ostream&	operator<<(std::ostream& os, const Form& form)
{
	os << "Form: " << form.getName() 
		<< ", Grade to sign: " << form.getGradeToSign() 
		<< ", Grade to execute: " << form.getGradeToExecute()
		<< ", Signed? " << (form.getSignedBool() ? "Yes" : "No");
	return (os);
}
