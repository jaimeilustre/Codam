/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Replacer.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/16 10:17:15 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/16 10:27:43 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACER_HPP
# define REPLACER_HPP

#include <string>

class Replacer
{
	public:
		Replacer(const std::string& filename, const std::string& s1, const std::string& s2);
		~Replacer();
		bool process();
	private:
		std::string filename;
		std::string s1;
		std::string s2;
		std::string replaceString(const std::string& line) const;
};

#endif