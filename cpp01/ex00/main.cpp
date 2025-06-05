/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:20:41 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/02 17:20:44 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Zombie.hpp"

Zombie* newZombie(std::string name);
void randomChump(std::string name);

int main(void)
{
	Zombie* heapZombie = newZombie("Clicker");
	heapZombie->announce();
	delete (heapZombie);
	randomChump("Runner");
	return (0);
}
