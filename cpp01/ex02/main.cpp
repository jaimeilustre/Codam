/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:21:49 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/02 17:21:51 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main(void)
{
	std::string str = "HI THIS IS BRAIN";

	std::string *stringPTR = &str; // pointer
	std::string &stringREF = str; // reference

	std::cout << "Address of str: " << &str << std::endl;
	std::cout << "Address of string pointer: " << stringPTR << std::endl;
	std::cout << "Address of string reference: " << &stringREF << std::endl;
	
	std::cout << "Value of str: " << str << std::endl;
	std::cout << "Value of string pointer: " << *stringPTR << std::endl;
	std::cout << "Value of string reference: " << stringREF << std::endl;
	
	return (0);
}
