/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 15:18:23 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/13 15:02:14 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int main(void)
{
	FragTrap	ft("FT-01");
	
	ft.attack("Target C");
	ft.takeDamage(50);
	ft.beRepaired(30);
	ft.takeDamage(80);
	ft.beRepaired(50);
	ft.attack("Target D");
	ft.highFivesGuys();

	return (0);
}
