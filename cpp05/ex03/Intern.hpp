/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Intern.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/30 15:32:37 by jilustre      #+#    #+#                 */
/*   Updated: 2025/09/30 16:04:45 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include <iostream>
# include <string>

class AForm;

class Intern
{
	public:
		Intern();
		Intern(const Intern& other);
		Intern&	operator=(const Intern& other);
		~Intern();

		AForm*	makeForm(const std::string& formName, const std::string& formTarget);
};

#endif