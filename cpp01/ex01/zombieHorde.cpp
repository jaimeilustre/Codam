/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   zombieHorde.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:21:41 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/02 17:21:43 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name)
{
	Zombie* horde = new Zombie[N];
	for (int i = 0; i < N; i++)
		horde[i].setName(name);
	return (horde);
}
