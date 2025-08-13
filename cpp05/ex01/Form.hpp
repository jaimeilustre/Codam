/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Form.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 10:58:16 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/08/13 15:16:50 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <exception>
# include <string>

# define MAX_GRADE 1
# define MIN_GRADE 150

# include "Bureaucrat.hpp"

class Form
{
	public:
		Form(const std::string& name, int gradeToSign, int gradeToExecute);
		Form(const Form& other);
		Form&	operator=(const Form& other);
		~Form();

		class GradeTooHighException: public std::exception
		{
			public:
				const char* what() const throw();
		};

		class GradeTooLowException: public std::exception
		{
			public:
				const char* what() const throw();
		};
		
		std::string const&	getName() const;
		bool				getSignedBool() const;
		int					getGradeToSign() const;
		int					getGradeToExecute() const;
		
		void				beSigned(const Bureaucrat& bureaucrat);
	private:
		std::string const	_name;
		bool				_signedForm;
		int const			_gradeToSign;
		int const			_gradeToExecute;
};

std::ostream&	operator<<(std::ostream& os, const Form& form);

#endif