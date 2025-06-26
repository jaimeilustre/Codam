/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 15:18:23 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/26 15:40:17 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap	ct("CL4P-TP");

	ct.attack("Target");
	ct.takeDamage(5);
	ct.beRepaired(3);
	ct.takeDamage(8);
	ct.beRepaired(5);
	ct.attack("New target");
	
	return (0);
}
