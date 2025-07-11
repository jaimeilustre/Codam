/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClapTrap.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 13:34:52 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/11 14:43:44 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "ClapTrap.hpp"

/*Default constructor*/
ClapTrap::ClapTrap()
{
	std::cout << "Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name): _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "Parameterized constructor called" << std::endl;
}

/*Copy constructor*/
ClapTrap::ClapTrap(const ClapTrap& other): _name(other._name), _hitPoints(other._hitPoints), _energyPoints(other._energyPoints), _attackDamage(other._attackDamage)
{
	std::cout << "Copy constructor called" << std::endl;
}

/*Copy assignment operator*/
ClapTrap&	ClapTrap::operator=(const ClapTrap& other)
{
	if (this != &other)
	{
		_name = other._name;
		_hitPoints = other._hitPoints;
		_energyPoints = other._energyPoints;
		_attackDamage = other._attackDamage;
	}
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << "Destructor called" << std::endl;
}

void	ClapTrap::attack(const std::string& target)
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
	std::cout << "ClapTrap " << _name <<  " attacks " << target << " causing " << _attackDamage << " points of damage!" << std::endl;
	_energyPoints--;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "No health left, you dead!" << std::endl;
		return ;
	}
	std::cout << _name << " taking " << amount << " points of damage!" << std::endl;
	if (amount >= _hitPoints)
		_hitPoints = 0;
	else
		_hitPoints -= amount;
	std::cout << "Health left: " << _hitPoints << " hit points" << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "No health left for healing, you dead!" << std::endl;
		return ;
	}
	else if (_energyPoints == 0)
	{
		std::cout << "No energy left for healing!" << std::endl;
		return ;
	}
	std::cout << "Healing..." << std::endl;
	_hitPoints += amount;
	_energyPoints--;
	std::cout << "New health: " << _hitPoints << " hit points" << std::endl;
}


