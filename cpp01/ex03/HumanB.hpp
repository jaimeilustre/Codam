/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   HumanB.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 10:21:28 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/02 11:00:46 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

# include <string>
# include "Weapon.hpp"

class HumanB
{
	public:
		HumanB(const std::string& name): name(name), weapon(nullptr) {}
		~HumanB();
		void attack() const;
		void setWeapon(Weapon& newWeapon);
	private:
		Weapon* weapon;
		std::string name;
};

#endif