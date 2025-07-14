/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   DiamondTrap.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 11:01:29 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/14 13:07:24 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

# include <iostream>
# include <string>

# include "ScavTrap.hpp"
# include "FragTrap.hpp"

class DiamondTrap: public ScavTrap, public FragTrap
{
	public:
		DiamondTrap();
		DiamondTrap(std::string name);
		DiamondTrap(const DiamondTrap& other);
		DiamondTrap&	operator=(const DiamondTrap& other);
		~DiamondTrap();
		
		void	attack(const std::string& target);
		void	whoAmI();
	private:
		std::string	_name;
};

#endif