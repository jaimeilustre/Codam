/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PhoneBook.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 07:19:24 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/24 16:02:35 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

#include <iostream>

void PhoneBook::addContact()
{
	Contact newContact;

	if (!newContact.addFirstName())
	{
		std::cout << "First name cannot be empty. Please add your first name" << std::endl;
		return ;
	}
	if (!newContact.addLastName())
	{
		std::cout << "Last name cannot be empty. Please add your last name" << std::endl;
		return ;
	}
	if (!newContact.addNickname())
	{
		std::cout << "Nickname cannot be empty. Please add your nickname" << std::endl;
		return ;
	}
	if (!newContact.addPhoneNumber())
	{
		std::cout << "Phone number cannot be empty. Please add your phone number" << std::endl;
		return ;
	}
	if (!newContact.addDarkestSecret())
	{
		std::cout << "C'mon don't be shy, this is a safe space" << std::endl;
		return ;
	}
	contacts[index] = newContact;
	std::cout << "Contact added to phonebook!" << std::endl;
}

int main(void)
{
	PhoneBook phoneBook;

	phoneBook.addContact();
	return (0);
}
