/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Account.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/27 18:36:52 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/05/29 11:14:19 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"

#include <ctime>
#include <iostream>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

/*Constructor*/
Account::Account(int initial_deposit)
{
	_accountIndex = _nbAccounts++;
	_amount = initial_deposit;
	_nbDeposits = 0;
	_nbWithdrawals = 0;
	_totalAmount += initial_deposit;

	_displayTimestamp();
	std::cout << "index:" << _accountIndex 
		<< ";amount:" << _amount 
		<< ";created" << std::endl;
}

/*Static getters*/
int Account::getNbAccounts()
{
	return (_nbAccounts);
}

int Account::getTotalAmount()
{
	return (_totalAmount);
}

int Account::getNbDeposits()
{
	return (_totalNbDeposits);
}

int Account::getNbWithdrawals()
{
	return (_totalNbWithdrawals);
}

void Account::displayAccountsInfos()
{
	_displayTimestamp();
	std::cout << "accounts:" << _nbAccounts  
		<< ";total:" << _totalAmount 
		<< ";deposits:" << _totalNbDeposits 
		<< ";withdrawals:" << _totalNbWithdrawals 
		<< std::endl;
}

void Account::_displayTimestamp()
{
	
	time_t timestamp = time(NULL);
	struct tm datetime = *localtime(&timestamp);
	
	char output[50];

	strftime(output, 50, "[%Y%m%d_%H%M%S] ", &datetime);
	std::cout << output;
}

int Account::checkAmount() const
{
	return (_amount);
}

void Account::displayStatus() const
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex 
		<< ";amount:" << _amount 
		<< ";deposits:" << _nbDeposits 
		<< ";withdrawals:" << _nbWithdrawals 
		<< std::endl;
}

void Account::makeDeposit(int deposit)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex 
		<< ";p_amount:" << _amount;
	
	_amount += deposit;
	_nbDeposits++;
	_totalAmount += deposit;
	_totalNbDeposits++;
	
	std::cout << ";deposit:" << deposit 
		<< ";amount:" << _amount 
		<< ";nb_deposits:" << _nbDeposits 
		<< std::endl; 
}

bool Account::makeWithdrawal(int withdrawal)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex 
		<< ";p_amount:" << _amount;
	
	if (withdrawal > _amount)
	{
		std::cout << ";withdrawal:refused" << std::endl;
		return (false);
	}
	
	_amount -= withdrawal;
	_nbWithdrawals++;
	_totalAmount -= withdrawal;
	_totalNbWithdrawals++;
	
	std::cout << ";withdrawal:" << withdrawal 
		<< ";amount:" << _amount 
		<< ";nb_withdrawals:" << _nbWithdrawals
		<< std::endl; 
	return (true);
}

/*Destructor*/
Account::~Account()
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex 
		<< ";amount:" << _amount 
		<< ";closed" << std::endl;
}

