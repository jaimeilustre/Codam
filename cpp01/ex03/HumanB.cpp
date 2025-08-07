/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   HumanB.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:22:17 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/16 11:16:05 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "HumanB.hpp"
#include "Weapon.hpp"

HumanB::HumanB(const std::string& name): name(name), weapon(nullptr)
{
	std::cout << "HumanB constructor called!" << std::endl;
}

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