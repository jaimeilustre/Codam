/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   HumanB.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:22:24 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/16 11:16:09 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

# include <string>
# include "Weapon.hpp"

class HumanB
{
	public:
		HumanB(const std::string& name);
		~HumanB();
		void attack() const;
		void setWeapon(Weapon& newWeapon);
	private:
		Weapon* weapon;
		std::string name;
};

#endif