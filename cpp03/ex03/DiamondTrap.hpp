/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   DiamondTrap.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 11:01:29 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/30 12:36:25 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

# include "ClapTrap.hpp"
# include "ScavTrap.hpp"
# include "FragTrap.hpp"

class DiamondTrap: public ScavTrap, public FragTrap
{
	public:
		DiamondTrap(std::string name);
		~DiamondTrap();
		
		void	attack(const std::string& target) override;
		void	whoAmI();
	private:
		std::string	_name;
};

#endif