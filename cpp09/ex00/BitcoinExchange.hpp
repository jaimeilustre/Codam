/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/24 11:30:15 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/12/24 11:36:45 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>

class BitcoinExchange
{
	private:
		std::string _date;
		int			_btcExchangeRate;
		int			_btcAmount;
		int			_btcPrice;

	public:
		// Orthodox Canonical Form
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange&	operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		// Getters
		std::string	getDate() const;
		int			getExchangeRate() const;
		int			getAmount() const;
		int			getPrice() const;
		
		// Print function
		void	printOutput();
};

#endif