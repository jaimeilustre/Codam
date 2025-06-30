/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScavTrap.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/26 16:28:36 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/30 12:30:20 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap: virtual public ClapTrap
{
	public:
		ScavTrap();
		ScavTrap(const std::string& name);
		~ScavTrap();

		void	attack(const std::string& target) override;
		void	guardGate();
};

#endif