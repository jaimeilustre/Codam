/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Replacer.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/16 11:13:55 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/16 11:16:39 by jilustre      ########   odam.nl         */
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