/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Character.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/22 15:49:00 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/31 07:49:13 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include "ICharacter.hpp"
# include "AMateria.hpp"

class Character: public ICharacter
{
	private:
		std::string	_name;
		AMateria*	_inventory[4];
		int			_inventoryCount;
		AMateria*	_floorInventory[4];
		int			_floorCount;
	public:
		Character();
		Character(std::string const& name);
		Character(const Character& other);
		Character&	operator=(const Character& other);
		virtual ~Character();

		virtual std::string const&	getName() const;
		virtual void				equip(AMateria* m);
		virtual void				unequip(int idx);
		virtual void				use(int idx, ICharacter& target);
		virtual bool				hasInventorySpace() const;
		virtual void				printInventory() const;
		virtual void 				printFloorInventory() const;
};

#endif