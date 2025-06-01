/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Zombie.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/01 14:45:00 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/01 15:23:54 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Zombie.hpp"

/*Constructor*/
Zombie::Zombie(std::string name)
{
	this->name = name;
	std::cout << "Constructor called for zombie " << name << std::endl;
}

void Zombie::announce(void)
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

/*Destructor*/
Zombie::~Zombie()
{
	std::cout << "Destructor called for zombie " << name << std::endl;
}
