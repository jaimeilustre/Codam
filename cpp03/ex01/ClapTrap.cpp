/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClapTrap.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 13:34:52 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/15 07:32:45 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(): _name("Default"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap " << _name << " default constructor called!" << std::endl;
	std::cout << std::endl;
}

ClapTrap::ClapTrap(std::string name): _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap " << _name << " constructor called!" << std::endl;
	std::cout << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other): _name(other._name), _hitPoints(other._hitPoints), _energyPoints(other._energyPoints), _attackDamage(other._attackDamage)
{
	std::cout << "Copy constructor called" << std::endl;
	std::cout << std::endl;
}

ClapTrap&	ClapTrap::operator=(const ClapTrap& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	std::cout << std::endl;
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
	std::cout << "ClapTrap " << _name << " destructor called!" << std::endl;
}

void	ClapTrap::attack(const std::string& target)
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
	std::cout << "ClapTrap " << _name <<  " attacks " << target << " causing " << _attackDamage << " points of damage!" << std::endl;
	_energyPoints--;
	std::cout << "Energy Points left: " << _energyPoints << std::endl;
	std::cout << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "Health: " << _hitPoints << " hit points" << std::endl;
		std::cout << "No health left, you dead!" << std::endl;
		std::cout << std::endl;
		return ;
	}
	std::cout << "Health: " << _hitPoints << " hit points" << std::endl;
	std::cout << _name << " taking " << amount << " points of damage!" << std::endl;
	if (amount >= _hitPoints)
		_hitPoints = 0;
	else
		_hitPoints -= amount;
	std::cout << "Health left: " << _hitPoints << " hit points" << std::endl;
	std::cout << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "Health: " << _hitPoints << " hit points" << std::endl;
		std::cout << "No health left for healing, you dead!" << std::endl;
		std::cout << std::endl;
		return ;
	}
	else if (_energyPoints == 0)
	{
			std::cout << "Energy Points: " << _energyPoints << std::endl;
		std::cout << "No energy left for healing!" << std::endl;
		std::cout << std::endl;
		return ;
	}
	std::cout << "Energy Points: " << _energyPoints << std::endl;
	std::cout << _name << " healing..." << std::endl;
	_hitPoints += amount;
	_energyPoints--;
	std::cout << "New health: " << _hitPoints << " hit points" << std::endl;
	std::cout << "Energy Points left: " << _energyPoints << std::endl;
	std::cout << std::endl;
}


