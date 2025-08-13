/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Form.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 10:58:16 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/08/13 11:14:13 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <exception>
# include <string>

# define MAX_GRADE 1
# define MIN_GRADE 150

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
		bool				getSignedBool();
		int					getGradeToSign();
		int					getGradeToExecute();
	private:
		std::string const	_name;
		bool				_signedForm;
		int					_gradeToSign;
		int					_gradeToExecute;
};

#endif