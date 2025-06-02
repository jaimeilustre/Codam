/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Weapon.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 10:34:16 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/02 10:52:43 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Weapon.hpp"

// Weapon::Weapon(const std::string& type)
// {
// 	std::cout << "Weapon constructor called" << std::endl;
// }

const std::string& Weapon::getType() const
{
	return (type);
}

void Weapon::setType(const std::string& newType)
{
	type = newType;
}

Weapon::~Weapon()
{
	std::cout << "Weapon destructor called" << std::endl;
}
