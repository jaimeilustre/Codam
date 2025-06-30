/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   DiamondTrap.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 11:23:23 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/30 12:37:26 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(std::string name): ClapTrap(name + "_clap_name"), ScavTrap(), FragTrap()
{
	this->_name = name;
	this->_hitPoints = 100; // FragTrap
	this->_energyPoints = 50;// ScavTrap
	this->_attackDamage = 30; // FragTrap
	
	std::cout << "DiamondTrap " << this->_name << " constructed!" << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap " << this->_name << " destroyed!" << std::endl;
}

void	DiamondTrap::attack(const std::string& target)
{
	ScavTrap::attack(target);
}

void	DiamondTrap::whoAmI()
{
	std::cout << "I am " << this->_name << ", ClassTrap: " << ClapTrap::_name << std::endl;
}


