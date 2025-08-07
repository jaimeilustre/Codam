/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Weapon.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:22:49 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/16 11:16:18 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <string>

class Weapon
{
	public:
		Weapon(const std::string& type);
		~Weapon();
		const std::string& getType() const;
		void setType(const std::string& newType);
	private:
		std::string type;
};

#endif