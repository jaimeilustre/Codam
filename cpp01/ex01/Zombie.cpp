/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Zombie.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:21:26 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/04 14:47:20 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Zombie.hpp"

/*Default constructor*/
Zombie::Zombie() 
{
	std::cout << "Default constructor called for zombie " << name << std::endl;
};

void Zombie::setName(std::string name)
{
	this->name = name;
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
