/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/01 15:09:06 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/01 16:55:25 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name);

int main(void)
{
	int nb = 5;
	Zombie* horde = zombieHorde(nb, "Clicker");
	for (int i = 0; i < nb; i++)
		horde[i].announce();
	delete[] horde;
	return (0);
}
