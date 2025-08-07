/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 15:18:23 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/15 07:25:19 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main(void)
{	
	ScavTrap	st("ST-01");
	
	st.attack("Target C");
	st.takeDamage(50);
	st.beRepaired(30);
	st.takeDamage(70);
	st.beRepaired(50);
	st.attack("Target D");
	st.guardGate();

	return (0);
}
