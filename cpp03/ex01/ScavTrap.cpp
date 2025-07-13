/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScavTrap.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 16:34:16 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/13 15:03:50 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
	std::cout << "ScavTrap " << _name << " default constructor called!" << std::endl;
	std::cout << std::endl;
}

ScavTrap::ScavTrap(const std::string& name): ClapTrap(name)
{
	std::cout << "ScavTrap " << _name << " constructor called!" << std::endl;
	std::cout << std::endl;
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
}

ScavTrap::ScavTrap(const ScavTrap& other): ClapTrap(other)
{
	std::cout << "Copy constructor called" << std::endl;
	std::cout << std::endl;
}

ScavTrap&	ScavTrap::operator=(const ScavTrap& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	std::cout << std::endl;
	if (this != &other)
		ClapTrap::operator=(other);
	return (*this);
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << _name << " destructor called!" << std::endl;
	std::cout << std::endl;
}

void	ScavTrap::attack(const std::string& target)
{
	if (_hitPoints == 0)
	{
		std::cout << "Health: " << _hitPoints << " hit points" << std::endl;
		std::cout << "No health left for attacking, you dead!" << std::endl;
		std::cout << std::endl;
		return ;
	}
	else if (_energyPoints == 0)
	{
		std::cout << "Energy Points: " << _energyPoints << std::endl;
		std::cout << "No energy left for attacking!" << std::endl;
		std::cout << std::endl;
		return ;
	}
	std::cout << "Energy Points: " << _energyPoints << std::endl;
	std::cout << "ScavTrap " << _name <<  " attacks " << target << " causing " << _attackDamage << " points of damage!" << std::endl;
	_energyPoints--;
	std::cout << "Energy Points left: " << _energyPoints << std::endl;
	std::cout << std::endl;
}

void	ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << _name << " is now in Gate keeper mode. YOU SHALL NOT PASS!!!" << std::endl;
	std::cout << std::endl;
}
