/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Harl.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 18:31:51 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/04 11:15:20 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

# include <string>

class Harl
{
	public:
		void complain(std::string level);
		int getLevel(const std::string& level);
	private:
		void debug(void);
		void info(void);
		void warning(void);
		void error(void);	
};

#endif
