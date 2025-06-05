/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   HumanA.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:22:03 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/04 14:55:18 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "HumanA.hpp"

void HumanA::attack() const
{
	std::cout << name << " attacks with their " << weapon.getType() << std::endl;
}

HumanA::~HumanA()
{
	std::cout << "Human A destructor called!" << std::endl;
}
