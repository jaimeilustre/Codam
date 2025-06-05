/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Weapon.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:22:41 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/02 17:22:43 by jilustre      ########   odam.nl         */
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
