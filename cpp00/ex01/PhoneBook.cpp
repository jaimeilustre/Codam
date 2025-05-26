/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PhoneBook.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 07:19:24 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/26 17:51:10 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

#include <iomanip>
#include <iostream>

void PhoneBook::addContact()
{
	Contact newContact;

	while (!newContact.addFirstName())
		std::cout << "First name cannot be empty. Please add your first name" << std::endl;
	while (!newContact.addLastName())
		std::cout << "Last name cannot be empty. Please add your last name" << std::endl;
	while (!newContact.addNickname())
		std::cout << "Nickname cannot be empty. Please add your nickname" << std::endl;
	while (!newContact.addPhoneNumber())
		std::cout << "Phone number cannot be empty. Please add your phone number" << std::endl;
	while (!newContact.addDarkestSecret())
		std::cout << "C'mon don't be shy, this is a safe space" << std::endl;
	contacts[index] = newContact;
	if (countContacts < 8)
		countContacts++;
	index = (index + 1) % 8;
	std::cout << "Contact added to phonebook!" << std::endl;
}

void PhoneBook::searchContact()
{
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
	std::string input;
	std::cout << "Please enter index of contact you want to see" << std::endl;
	std::getline(std::cin, input);
	int inputInt = std::atoi(input.c_str());
	if (inputInt == index)
		contacts[inputInt].displaySpecificContact();
	else
		std::cout << "Invalid index number" << std::endl;	
}

int main(void)
{
	PhoneBook phoneBook;
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
