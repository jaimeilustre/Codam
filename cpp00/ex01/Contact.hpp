/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Contact.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 07:24:24 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/23 16:43:34 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

class Contact
{
private:
	std::string firstName;
	std::string lastName;
	std::string nickname;
	std::string phoneNumber;
	std::string darkestSecret;
public:
	bool addFirstName();
	bool addLastName();
	bool addNickname();
	bool addPhoneNumber();
	bool addDarkestSecret();
	void displaySavedContacts(int index);
	void displaySpecificContact();
};

#endif
