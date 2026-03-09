/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/24 11:30:15 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2026/03/09 12:05:36 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <fstream>
# include <iostream>
# include <map>
# include <string>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_exchangeRates;
		
		bool	leapYearCheck(int year) const;
		bool	validDateCheck(const std::string& date) const;
		double	getExchangeRate(const std::string& date) const;
	
	public:
		// Orthodox Canonical Form
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange&	operator=(const BitcoinExchange& other);
		~BitcoinExchange();
	
		void	loadDb(const std::string& filename);
		void	processTextFile(const std::string& filename) const;
};

#endif