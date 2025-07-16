/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Animal.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 16:12:24 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/16 17:11:07 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

class Animal
{
	public:
		Animal();
		Animal(const Animal& other);
		Animal&	operator=(const Animal& other);
		~Animal();
		
		void	makeSound() const;
		void	setType(const std::string& type);
		std::string	getType() const;
		
	protected:
		std::string	_type;
};

#endif