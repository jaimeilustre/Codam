/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FragTrap.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/27 12:06:13 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/15 07:27:13 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(): ClapTrap("Default")
{
	std::cout << "FragTrap " << _name << " default constructor called!" << std::endl;
	std::cout << std::endl;
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
}

FragTrap::FragTrap(const std::string& name): ClapTrap(name)
{
	std::cout << "FragTrap " << _name << " constructor called!" << std::endl;
	std::cout << std::endl;
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
}

FragTrap::FragTrap(const FragTrap& other): ClapTrap(other)
{
	std::cout << "Copy constructor called" << std::endl;
	std::cout << std::endl;
}

FragTrap&	FragTrap::operator=(const FragTrap& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	std::cout << std::endl;
	if (this != &other)
		ClapTrap::operator=(other);
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << _name << " destructor called!" << std::endl;
	std::cout << std::endl;
}

void	FragTrap::attack(const std::string& target)
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
	std::cout << "FragTrap " << _name <<  " attacks " << target << " causing " << _attackDamage << " points of damage!" << std::endl;
	_energyPoints--;
	std::cout << "Energy Points left: " << _energyPoints << std::endl;
	std::cout << std::endl;
}

void	FragTrap::highFivesGuys()
{
	if (_hitPoints == 0)
	{
		std::cout << "No health left for giving high fives" << std::endl;
		std::cout << std::endl;
		return ;
	}
	std::cout << "FragTrap " << _name << " says high-five!" << std::endl;
	std::cout << std::endl;
}


