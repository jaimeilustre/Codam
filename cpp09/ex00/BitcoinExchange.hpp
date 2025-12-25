/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/24 11:30:15 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/12/25 16:02:22 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <fstream>
# include <map>
# include <string>
# include <iostream>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_exchangeRates;
		
		bool	validDateCheck(const std::string& date) const;
		double	getExchangeRate(const std::string& date) const;
	
	public:
		// Orthodox Canonical Form
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange&	operator=(const BitcoinExchange& other);
		~BitcoinExchange();
	
		void	loadDb(const std::string& filename);
		void	processFile(const std::string& filename) const;
};

#endif