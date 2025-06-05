/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:21:20 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/02 17:21:22 by jilustre      ########   odam.nl         */
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
