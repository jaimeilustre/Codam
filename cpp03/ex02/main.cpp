/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 15:18:23 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/27 14:50:46 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "ClapTrap.hpp"
#include "FragTrap.hpp"

int main(void)
{
	std::cout << "Creating ClapTrap:" << std::endl;
	ClapTrap	ct("CT-01");
	ct.attack("Target A");
	ct.takeDamage(5);
	ct.beRepaired(3);
	ct.takeDamage(8);
	ct.beRepaired(5);
	ct.attack("Target B");
	std::cout << std::endl;
	
	std::cout << "Creating FragTrap:" << std::endl;
	FragTrap	ft("FT-01");
	ft.attack("Target C");
	ft.takeDamage(50);
	ft.beRepaired(30);
	ft.takeDamage(80);
	ft.beRepaired(50);
	ft.attack("Target D");
	ft.highFivesGuys();
	std::cout << std::endl;

	std::cout << "Testing polymorphism:" << std::endl;
	ClapTrap	*ptr = new FragTrap("PF-01");
	ptr->attack("Target E");
	delete (ptr);
	
	return (0);
}
