/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 15:18:23 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/27 10:47:29 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

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
	
	std::cout << "Creating ScavTrap:" << std::endl;
	ScavTrap	st("ST-01");
	st.attack("Target C");
	st.takeDamage(50);
	st.beRepaired(30);
	st.takeDamage(80);
	st.beRepaired(50);
	st.attack("Target D");
	st.guardGate();
	std::cout << std::endl;

	std::cout << "Testing polymorphism:" << std::endl;
	ClapTrap	*ptr = new ScavTrap("PS-01");
	ptr->attack("Target E");
	delete (ptr);
	
	return (0);
}
