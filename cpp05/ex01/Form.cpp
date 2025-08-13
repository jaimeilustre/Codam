/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Form.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 11:06:44 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/08/13 11:21:43 by jaimeilustr   ########   odam.nl         */
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
	_name(other._name), _signedForm(other._signedForm), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
	std::cout << "Form copy constructor called!" << std::endl;
}

Form&	Form::operator=(const Form& other)
{
	std::cout << "Form copy assignment operator called!" << std::endl;
	if (this != &other)
	{
		_signedForm = other._signedForm; 
		_gradeToSign = other._gradeToSign;
		_gradeToExecute = other._gradeToExecute;
	}
	return (*this);
}