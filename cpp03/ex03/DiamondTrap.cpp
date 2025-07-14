/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   DiamondTrap.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 11:23:23 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/14 12:40:34 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
{
	std::cout << "DiamondTrap: " << _name << " default constructor called!" << std::endl;
	std::cout << std::endl;
}

DiamondTrap::DiamondTrap(std::string name)
	: ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), _name(name)
{
	std::cout << "DiamondTrap " << _name << " constructor called!" << std::endl;
	std::cout << std::endl;
	_hitPoints = 100; // FragTrap
	_energyPoints = 50; // ScavTrap
	_attackDamage = 30; // FragTrap
}

DiamondTrap::DiamondTrap(const DiamondTrap& other)
	: ClapTrap(other), ScavTrap(other), FragTrap(other), _name(other._name)
{
	std::cout << "Copy constructor called" << std::endl;
	std::cout << std::endl;
}

DiamondTrap&	DiamondTrap::operator=(const DiamondTrap& other)
{
	std::cout << "Copy assignment operator called!" << std::endl;
	std::cout << std::endl;
	if (this != &other)
	{
		ClapTrap::operator=(other);
		ScavTrap::operator=(other);
		FragTrap::operator=(other);
		_name = other._name;
	}
	return (*this);
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap " << _name << " destructor called!" << std::endl;
	std::cout << std::endl;
}

void	DiamondTrap::attack(const std::string& target)
{
	ScavTrap::attack(target);
}

void	DiamondTrap::whoAmI()
{
	std::cout << "I am " << _name << ", ClapTrap: " << ClapTrap::_name << std::endl;
	std::cout << std::endl;
}


