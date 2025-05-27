/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Contact.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 07:24:21 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/27 10:07:41 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

#include <iomanip>
#include <iostream>

bool Contact::addFirstName()
{
	std::string input;
	
	std::cout << "Enter first name: ";
	if (!std::getline(std::cin, input))
		return (false);
	if (input.empty())
		return (false);
	firstName = input;
	return (true);
}

bool Contact::addLastName()
{
	std::string input;
	
	std::cout << "Enter last name: ";
	if (!std::getline(std::cin, input))
		return (false);
	if (input.empty())
		return (false);
	lastName = input;
	return (true);
}

bool Contact::addNickname()
{
	std::string input;
	
	std::cout << "Enter nickname: ";
	if (!std::getline(std::cin, input))
		return (false);
	if (input.empty())
		return (false);
	nickname = input;
	return (true);
}

bool Contact::addPhoneNumber()
{
	std::string input;

	std::cout << "Enter phone number: ";
	if (!std::getline(std::cin, input))
		return (false);
	if (input.empty())
		return (false);
	phoneNumber = input;
	return (true);
}

bool Contact::addDarkestSecret()
{
	std::string input;

	std::cout << "Enter darkest secret: ";
	if (!std::getline(std::cin, input))
		return (false);
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
	std::cout << std::setw(10) << index << "|"
				<< std::setw(10) << truncateInput(firstName)  << "|" 
				<< std::setw(10) << truncateInput(lastName) << "|" 
				<< std::setw(10) << truncateInput(nickname) << std::endl;
}
