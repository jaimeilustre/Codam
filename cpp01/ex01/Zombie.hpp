/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Zombie.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:21:33 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/04 14:47:08 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>

class Zombie
{
	public:
		Zombie();
		~Zombie();
		void announce(void);
		void setName(std::string name);
	private:
		std::string name;
};

#endif