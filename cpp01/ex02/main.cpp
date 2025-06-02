/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 08:53:08 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/02 09:03:53 by jaimeilustr   ########   odam.nl         */
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
