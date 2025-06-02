/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Weapon.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 10:01:49 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/02 10:47:40 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <string>

class Weapon
{
	public:
		Weapon(const std::string& type) : type(type) {}
		~Weapon();
		const std::string& getType() const;
		void setType(const std::string& newType);
	private:
		std::string type;
};

#endif