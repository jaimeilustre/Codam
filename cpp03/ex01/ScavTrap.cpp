/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScavTrap.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 16:34:16 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/26 17:46:16 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
	std::cout << "ScavTrap " << _name << " default constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string& name): ClapTrap(name)
{
	std::cout << "ScavTrap " << _name << " constructor called" << std::endl;
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << _name << " destructor called" << std::endl;
}

void	ScavTrap::attack(const std::string& target)
{
	if (_hitPoints == 0)
	{
		std::cout << "No health left for attacking, you dead!" << std::endl;
		return ;
	}
	else if (_energyPoints == 0)
	{
		std::cout << "No energy left for attacking!" << std::endl;
		return ;
	}
	std::cout << "ScavTrap " << _name <<  " attacks " << target << " causing " << _attackDamage << " points of damage!" << std::endl;
	_energyPoints--;
}

void	ScavTrap::guardGate()
{
	std::cout << "ScavTrap is now in Gate keeper mode. YOU SHALL NOT PASS!!!" << std::endl;
}