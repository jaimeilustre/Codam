/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 15:18:23 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/14 12:56:37 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main(void)
{
	DiamondTrap	dt("DT-01");
	
	dt.attack("Target F");
	dt.takeDamage(50);
	dt.beRepaired(30);
	dt.takeDamage(80);
	dt.beRepaired(50);
	dt.attack("Target D");
	dt.whoAmI();
	
	return (0);
}
