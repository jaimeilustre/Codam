/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/24 15:51:31 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/12/24 16:50:45 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool	BitcoinExchange::validDateCheck(const std::string& date) const
{
	if (date.length() != 10)
		return (false);
	
	if (date[4] != '-' || date[7] != '-')
		return (false);
	
	int	year = std::atoi(date.substr(0, 4).c_str());
	int	month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return (false);

	int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (day < 1 || day > monthDays[month - 1])
		return (false);
		
	return (true);
}

double	BitcoinExchange::getExchangeRate(const std::string& date) const
{
	std::map<std::string, double>::const_iterator	it;
	it = _exchangeRates.lower_bound(date);

	if (it != _exchangeRates.end() && it->first == date)
		return (it->second);
	
	if (it == _exchangeRates.begin())
		throw std::runtime_error("No earlier date possible");
	
	--it;
	return (it->second);
}

void	BitcoinExchange::loadDb(const std::string& filename)
{
	std::ifstream	inputFile(filename.c_str());
	
	if (!inputFile)
		throw std::runtime_error("Cannot open file");
	
	std::string	line;
	
	std::getline(inputFile, line);
	while (std::getline(inputFile, line))
	{
		size_t	comma = line.find(',');
		if (comma == std::string::npos)
			continue ;
		std::string date = line.substr(0, comma);
		double rate = std::atof(line.substr(comma + 1).c_str());
		_exchangeRates[date] = rate;
	}
}
