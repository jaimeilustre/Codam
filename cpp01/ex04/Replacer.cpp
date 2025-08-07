/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Replacer.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/16 11:14:01 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/17 08:45:39 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <string>

#include "Replacer.hpp"

Replacer::Replacer(const std::string& filename, const std::string& s1, const std::string& s2): filename(filename), s1(s1), s2(s2)
{
	std::cout << "Replacer constructor called!" << std::endl;
}

std::string Replacer::replaceString(const std::string& input) const
{
	std::string	updatedInput;
	size_t		position;
	size_t		first_occurence;

	position = 0;
	first_occurence = input.find(s1, position);
	while (first_occurence != std::string::npos)
	{
		updatedInput += input.substr(position, first_occurence - position); //append up to the first occurence of s1
		updatedInput += s2; // append s2 that replaces s1
		position = s1.length() + first_occurence; // update position to be after the just replaced s1
		first_occurence = input.find(s1, position); // move to next position
	}
	updatedInput += input.substr(position);
	return (updatedInput);
}

bool Replacer::process()
{
	if (s1.empty())
	{
		std::cerr << "s1 cannot be empty!" << std::endl;
		return (false);
	}
	std::ifstream inputFile(filename);
	if (!inputFile)
	{
		std::cerr << "Cannot open file!" << std::endl;
		return (false);
	}
	std::ofstream outputFile(filename += ".replace");
	if (!outputFile)
	{
		std::cerr << "Cannot create output file!" << std::endl;
		return (false);
	}
	std::string line;
	while (std::getline(inputFile, line))
		outputFile << replaceString(line) << std::endl;
	inputFile.close();
	outputFile.close();
	return (true);
}

Replacer::~Replacer()
{
	std::cout << "Replacer destructor called!" << std::endl;
}



