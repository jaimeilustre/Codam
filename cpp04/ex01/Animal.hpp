/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Animal.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 16:12:24 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/31 06:14:04 by jaimeilustr   ########   odam.nl         */
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
		virtual ~Animal();
		
		virtual void	makeSound() const;
		std::string		getType() const;
	protected:
		std::string	type;
};

#endif