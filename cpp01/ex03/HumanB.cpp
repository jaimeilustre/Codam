/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   HumanB.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:22:17 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/02 17:22:19 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "HumanB.hpp"
#include "Weapon.hpp"

void HumanB::attack() const
{
	if (weapon)
		std::cout << name << " attacks with their " << weapon->getType() << std::endl;
	else
		std::cout << name << " has no weapon " << std::endl;
}

void HumanB::setWeapon(Weapon& newWeapon)
{
	weapon = &newWeapon;
}

HumanB::~HumanB()
{
	std::cout << "Human B destructor called!" << std::endl;
}