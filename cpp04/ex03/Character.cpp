/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Character.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/26 16:49:36 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/07/26 17:13:43 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character(std::string const& name): _name(name), _floorCount(0)
{
	std::cout << "Character constructor called!\n" << std::endl;
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
	for (int i = 0; i < 100; i++)
		_floorInventory[i] = NULL;
}

Character::Character(const Character& other): _name(other._name), _floorCount(0)
{
	std::cout << "Character copy constructor called!\n" << std::endl;
	for (int i = 0; i < 4; i++)
		_inventory[i] = other._inventory[i] ? other._inventory[i]->clone() : NULL;
	for (int i = 0; i < 100; i++)
		_floorInventory[i] = other._floorInventory[i] ? other._floorInventory[i]->clone() : NULL;	
}

Character&	Character::operator=(const Character& other)
{
	std::cout << "Character copy assignment operator called!\n" << std::endl;
	if (this != &other)
	{
		_name = other._name;
		for (int i = 0; i < 4; i++)
		{
			delete _inventory[i];
			_inventory[i] = other._inventory[i] ? other._inventory[i]->clone() : NULL;
		}
	}
	return (*this);
}

Character::~Character()
{
	std::cout << "Character destructor called!\n" << std::endl;
	for (int i = 0; i < 4; i++)
		delete _inventory[i];
	for (int i = 0; i < 100; i++)
		delete _floorInventory[i];
}

std::string const&	Character::getName() const
{
	return (_name);
}

void	Character::equip(AMateria* m)
{
	if (!m)
		return ;
	for (int i = 0; i < 4; i++)
	{
		if (!_inventory[i])
		{
			_inventory[i] = m;
			return ;
		}
	}
}

void	Character::unequip(int idx)
{
	if (idx >= 0 && idx <= 4 && _inventory[idx])
	{
		if (_floorCount < 100)
			_floorInventory[_floorCount++] = _inventory[idx];
		_inventory[idx] = NULL;
	}
}

void	Character::use(int idx, ICharacter& target)
{
	if (idx >= 0 && idx <= 4 && _inventory[idx])
		_inventory[idx]->use(target);
}

