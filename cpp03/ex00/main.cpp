/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 15:18:23 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/13 10:53:02 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap	ct("CT-01");

	ct.attack("Target A");
	ct.takeDamage(5);
	ct.beRepaired(3);
	ct.takeDamage(8);
	ct.beRepaired(5);
	ct.attack("Target B");
	
	return (0);
}
