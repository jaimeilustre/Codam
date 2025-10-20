/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ShrubberyCreationForm.cpp                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/24 15:34:38 by jilustre      #+#    #+#                 */
/*   Updated: 2025/10/20 14:16:12 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target): AForm("Shrubbery Creation", 145, 137), _target(target)
{
	std::cout << "ShrubbberyCreationForm constructor called!" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other): AForm(other), _target(other._target)
{
	std::cout << "ShrubberyCreationForm copy constructor called!\n" << std::endl;
}

ShrubberyCreationForm&	ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	std::cout << "ShrubberyCreationForm copy assignment operator called!\n" << std::endl;
	if (this != &other)
		_target = other._target;
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "ShrubberyCreationForm destructor called!" << std::endl;
}

void	ShrubberyCreationForm::execute(Bureaucrat const& executor) const
{
	if (!getSignedBool())
		throw NotSignedException();
	if (executor.getGrade() > getGradeToExecute())
		throw GradeTooLowException();
	std::ofstream outputFile(_target + "_shrubbery");
	outputFile << "       _-_" << std::endl;
    outputFile << "    /~~   ~~\\" << std::endl;
    outputFile << " /~~         ~~\\" << std::endl;
    outputFile << "{               }" << std::endl;
    outputFile << " \\  _-     -_  /" << std::endl;
    outputFile << "   ~  \\\\ //  ~" << std::endl;
    outputFile << "_- -   | | _- _" << std::endl;
    outputFile << "  _ -  | |   -_" << std::endl;
    outputFile << "      // \\\\" << std::endl;
	outputFile.close();
}