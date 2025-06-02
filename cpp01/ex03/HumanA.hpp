/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   HumanA.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 10:10:47 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/02 11:02:31 by jaimeilustr   ########   odam.nl         */
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