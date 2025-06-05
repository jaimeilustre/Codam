/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   HumanA.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:22:10 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/02 17:22:12 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

# include <string>
# include "Weapon.hpp"

class HumanA
{
	public:
		HumanA(const std::string& name, Weapon& weapon): name(name), weapon(weapon) {}
		~HumanA();
		void attack() const;
	private:
		Weapon& weapon;
		std::string name;
};

#endif