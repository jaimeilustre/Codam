/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 15:18:23 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/15 07:27:29 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int main(void)
{
	FragTrap	ft("FT-01");
	
	ft.attack("Target C");
	ft.takeDamage(50);
	ft.beRepaired(30);
	ft.takeDamage(70);
	ft.beRepaired(50);
	ft.attack("Target D");
	ft.highFivesGuys();

	return (0);
}
