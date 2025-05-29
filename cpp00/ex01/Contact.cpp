/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Contact.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 07:24:21 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/29 22:14:59 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

#include <iomanip>
#include <iostream>

bool Contact::addFirstName()
{
	std::string input;
	size_t		start;
	size_t		end;
	std::string trimmedInput;
	
	std::cout << "Enter first name: ";
	if (!std::getline(std::cin, input))
		return (false);
	start = 0;
	while (start < input.length() && std::isspace((input[start])))
		start++;
	end = input.length();
	while (end > start && std::isspace((input[end - 1])))
		end--;
	trimmedInput = input.substr(start, end - start);
	if (trimmedInput.empty())
	{
		std::cout << "First name cannot be empty. Please add your first name" << std::endl;
		return (false);
	}
	firstName = trimmedInput;
	return (true);
}

bool Contact::addLastName()
{
	std::string input;
	size_t		start;
	size_t		end;
	std::string trimmedInput;
	
	std::cout << "Enter last name: ";
	if (!std::getline(std::cin, input))
		return (false);
	start = 0;
	while (start < input.length() && std::isspace((input[start])))
		start++;
	end = input.length();
	while (end > start && std::isspace((input[end - 1])))
		end--;
	trimmedInput = input.substr(start, end - start);
	if (trimmedInput.empty())
	{
		std::cout << "Last name cannot be empty. Please add your last name" << std::endl;
		return (false);
	}
	lastName = trimmedInput;
	return (true);
}

bool Contact::addNickname()
{
	std::string input;
	size_t		start;
	size_t		end;
	std::string trimmedInput;
	
	std::cout << "Enter nickname: ";
	if (!std::getline(std::cin, input))
		return (false);
	start = 0;
	while (start < input.length() && std::isspace((input[start])))
		start++;
	end = input.length();
	while (end > start && std::isspace((input[end - 1])))
		end--;
	trimmedInput = input.substr(start, end - start);
	if (trimmedInput.empty())
	{
		std::cout << "Nickname cannot be empty. Please add your nickname" << std::endl;
		return (false);
	}
	nickname = trimmedInput;
	return (true);
}

bool Contact::addPhoneNumber()
{
	std::string input;
	size_t		start;
	size_t		end;
	std::string trimmedInput;

	std::cout << "Enter phone number: ";
	if (!std::getline(std::cin, input))
		return (false);
	start = 0;
	while (start < input.length() && std::isspace((input[start])))
		start++;
	end = input.length();
	while (end > start && std::isspace((input[end - 1])))
		end--;
	trimmedInput = input.substr(start, end - start);
	if (trimmedInput.empty())
	{
		std::cout << "Phone number cannot be empty. Please add your phone number" << std::endl;
		return (false);
	}
	for (char c : trimmedInput)
	{
		if (!std::isdigit(c))
		{
			std::cout << "Phone number must contain only digits" << std::endl;
			return (false);
		}
	}
	phoneNumber = trimmedInput;
	return (true);
}

bool Contact::addDarkestSecret()
{
	std::string input;
	size_t		start;
	size_t		end;
	std::string trimmedInput;

	std::cout << "Enter darkest secret: ";
	if (!std::getline(std::cin, input))
		return (false);
	start = 0;
	while (start < input.length() && std::isspace((input[start])))
		start++;
	end = input.length();
	while (end > start && std::isspace((input[end - 1])))
		end--;
	trimmedInput = input.substr(start, end - start);
	if (trimmedInput.empty())
	{
		std::cout << "C'mon don't be shy, this is a safe space" << std::endl;
		return (false);
	}
	darkestSecret = trimmedInput;
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
