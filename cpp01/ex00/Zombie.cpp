/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Zombie.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:21:06 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/02 17:21:09 by jilustre      ########   odam.nl         */
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
