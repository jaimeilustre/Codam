/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Zombie.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/01 14:35:02 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/01 17:07:20 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>

class Zombie
{
	public:
		Zombie();
		// Zombie(std::string name);
		~Zombie();
		void announce(void);
		void setName(std::string name);
	private:
		std::string name;
};

#endif