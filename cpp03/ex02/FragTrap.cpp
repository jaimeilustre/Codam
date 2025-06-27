/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FragTrap.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/27 12:06:13 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/27 12:15:58 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "ClapTrap.hpp"
#include "FragTrap.hpp"

FragTrap::FragTrap()
{
	std::cout << "FragTrap " << _name << " default constructor called!" << std::endl;
}

FragTrap::FragTrap(const std::string& name): ClapTrap(name)
{
	std::cout << "FragTrap " << _name << " constructor called!" << std::endl;
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << _name << " destructor called!" << std::endl;
}

void	FragTrap::attack(const std::string& target)
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
	std::cout << "FragTrap " << _name <<  " attacks " << target << " causing " << _attackDamage << " points of damage!" << std::endl;
	_energyPoints--;
}

void	FragTrap::highFivesGuys()
{
	std::cout << "FragTrap " << _name << " says high-five!" << std::endl;
}


