/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Zombie.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/01 14:45:00 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/01 17:07:30 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Zombie.hpp"

/*Default constructor*/
Zombie::Zombie() 
{
	this->name = "Unnamed";
	std::cout << "Default constructor called for zombie " << name << std::endl;
};

// /*Constructor*/
// Zombie::Zombie(std::string name)
// {
// 	this->name = name;
// 	std::cout << "Param constructor called for zombie " << name << std::endl;
// }

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
