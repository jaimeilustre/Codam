/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PhoneBook.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 07:19:24 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/30 08:22:50 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <iostream>

#include "PhoneBook.hpp"

void PhoneBook::addContact()
{
	Contact newContact;

	while (!newContact.addFirstName())
	{
		if (std::cin.eof())
			return ;
	}
	while (!newContact.addLastName())
	{
		if (std::cin.eof())
			return ;
	}
	while (!newContact.addNickname())
	{
		if (std::cin.eof())
			return ;
	}
	while (!newContact.addPhoneNumber())
	{
		if (std::cin.eof())
			return ;
	}
	while (!newContact.addDarkestSecret())
	{
		if (std::cin.eof())
			return ;
	}
	contacts[index] = newContact;
	if (countContacts < 8)
		countContacts++;
	index = (index + 1) % 8;
	std::cout << "Contact added to phonebook!" << std::endl;
}

void PhoneBook::searchContact()
{
	std::string input;
	int			inputInt;
	
	if (countContacts == 0)
	{
		std::cout << "Phonebook is empty!" << std::endl;
		return ;
	}
	std::cout << std::setw(10) << "Index" << "|" 
				<< std::setw(10) << "First name" << "|" 
				<< std::setw(10) << "Last name" << "|" 
				<< std::setw(10) << "Nickname" << std::endl;
	for (int i = 0; i < countContacts; i++)
		contacts[i].displaySavedContacts(i);
	std::cout << "Please enter index of contact you want to see" << std::endl;
	std::getline(std::cin, input);
	inputInt = std::stoi(input);
	if (inputInt < 0 || inputInt >= countContacts)
		std::cout << "Invalid index number" << std::endl;
	else
		contacts[inputInt].displaySpecificContact();	
}

int main(void)
{
	PhoneBook	phoneBook;
	std::string	input;

	std::cout << "Welcome to my phonebook!" << std:: endl;
	std::cout << "Please enter ADD, SEARCH, or EXIT" << std::endl;
	while (true)
	{
		if (!std::getline(std::cin, input))
			break ;
		if (input == "ADD")
			phoneBook.addContact();
		else if (input == "SEARCH")
			phoneBook.searchContact();
		else if (input == "EXIT")
		{
			std::cout << "Exiting phonebook..." << std::endl;
			break ;
		}
		else
			std::cout << "Invalid command, please try again" << std::endl;
	}
	return (0);
}
