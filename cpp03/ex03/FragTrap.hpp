/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FragTrap.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/27 11:33:38 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/14 10:57:16 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"

class FragTrap: virtual public ClapTrap
{
	public:
		FragTrap();
		FragTrap(const std::string& name);
		FragTrap(const FragTrap& other);
		FragTrap&	operator=(const FragTrap& other);
		~FragTrap();

		void	attack(const std::string& target);
		void	highFivesGuys(void);
};

#endif