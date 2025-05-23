/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Contact.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 07:24:21 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/24 15:06:48 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

#include <iomanip>
#include <iostream>

bool Contact::addFirstName()
{
	std::string input;
	
	std::cout << "Enter first name: ";
	getline(std::cin, input);
	if (input.empty())
		return (false);
	firstName = input;
	return (true);
}

bool Contact::addLastName()
{
	std::string input;
	
	std::cout << "Enter last name: ";
	getline(std::cin, input);
	if (input.empty())
		return (false);
	lastName = input;
	return (true);
}

bool Contact::addNickname()
{
	std::string input;
	
	std::cout << "Enter nickname: ";
	getline(std::cin, input);
	if (input.empty())
		return (false);
	nickname = input;
	return (true);
}

bool Contact::addPhoneNumber()
{
	std::string input;

	std::cout << "Enter phone number: ";
	getline(std::cin, input);
	if (input.empty())
		return (false);
	phoneNumber = input;
	return (true);
}

bool Contact::addDarkestSecret()
{
	std::string input;

	std::cout << "Enter darkest secret: ";
	getline(std::cin, input);
	if (input.empty())
		return (false);
	darkestSecret = input;
	return (true);
}

void Contact::displaySpecificContact()
{
	std::cout << "First name: " << firstName << std::endl;
	std::cout << "Last name: " << lastName << std::endl;
	std::cout << "Nickname: " << nickname << std::endl;
	std::cout << "Phone number: " << phoneNumber << std::endl;
	std::cout << "Darkest secret: " << darkestSecret << std::endl;
}

std::string truncateInput(std::string& str)
{
	if (str.length() > 10)
		return (str.substr(0, 8) += ".");
	return (str);	
}

void Contact::displaySavedContacts(int index)
{
	std::cout << std::setw(10) << index << std::setw(10) << "|" << std::setw(10)
		<< truncateInput(firstName) << std::setw(10) << "|" << std::setw(10)
		<< truncateInput(lastName) << std::setw(10) << "|" << std::setw(10)
		<< truncateInput(nickname);
}

// int main(void)
// {
// 	Contact newContact;
	
// 	newContact.addFirstName();
// 	newContact.addLastName();
// 	newContact.addNickname();
// 	newContact.addPhoneNumber();
// 	newContact.addDarkestSecret();
	
// 	return (0);
// }
