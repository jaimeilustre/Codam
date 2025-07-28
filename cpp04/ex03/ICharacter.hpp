/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ICharacter.hpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/22 15:20:22 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/07/28 10:59:02 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ICHARACTER_HPP
# define ICHARACTER_HPP

# include <string>

class AMateria;

class ICharacter
{
	public:
		virtual ~ICharacter() {};
		virtual std::string const&	getName() const = 0;
		virtual void				equip(AMateria* m) = 0;
		virtual void				unequip(int idx) = 0;
		virtual void				use(int idx, ICharacter& target) = 0;		
};

#endif