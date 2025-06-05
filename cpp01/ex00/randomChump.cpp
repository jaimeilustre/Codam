/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   randomChump.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:21:00 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/02 17:21:02 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#include "Zombie.hpp"

void randomChump(std::string name)
{
	Zombie zombie(name);
	zombie.announce();
}
