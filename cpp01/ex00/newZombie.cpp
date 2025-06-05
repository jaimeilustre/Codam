/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   newZombie.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:20:51 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/02 17:20:54 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#include "Zombie.hpp"

Zombie* newZombie(std::string name)
{
	return new Zombie(name);
}
