/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   AForm.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 10:58:16 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/08/18 11:39:00 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP

# include <iostream>
# include <exception>
# include <string>

# define MAX_GRADE 1
# define MIN_GRADE 150

class Bureaucrat;

class AForm
{
	public:
		AForm(const std::string& name, int gradeToSign, int gradeToExecute);
		AForm(const AForm& other);
		AForm&	operator=(const AForm& other);
		virtual ~AForm();

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

		virtual void		execute(Bureaucrat const& executor) = 0;
	private:
		std::string const	_name;
		bool				_signedForm;
		int const			_gradeToSign;
		int const			_gradeToExecute;
};

std::ostream&	operator<<(std::ostream& os, const AForm& form);

#endif