/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaimeilustre <jaimeilustre@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 06:12:48 by jaimeilustr   #+#    #+#                 */
/*   Updated: 2025/06/03 07:28:55 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <string>

const std::string replaceString(const std::string& input, const std::string& s1, const std::string& s2)
{
	std::string	updatedInput;
	size_t		position;
	size_t		first_occurence;

	if (s1.empty())
		return (input);
	position = 0;
	first_occurence = input.find(s1, position);
	while (first_occurence != std::string::npos)
	{
		updatedInput += input.substr(position, first_occurence - position); //append up to the first occurence of s1
		updatedInput += s2; // append s2 that replaces s1
		position = s1.length() + first_occurence; // update position to be after the appended s2
		first_occurence = input.find(s1, position); // move to next position
	}
	updatedInput += input.substr(position);
	return (updatedInput);
}

int main(int argc, char **argv)
{
	std::string	file;
	std::string	s1;
	std::string	s2;
	std::string	line;
	
	if (argc != 4)
	{
		std::cerr << "Insufficient/Too many arguments!" << std::endl;
		return (1);	
	}
	else
	{
		file = argv[1];
		s1 = argv[2];
		s2 = argv[3];
		
		std::ifstream input(file);
		if (!input)
		{
			std::cerr << "Cannot open file!" << std::endl;
			return (1);
		}
		std::ofstream output(file += ".replace");
		if (!output)
		{
			std::cerr << "Cannot create output file!" << std::endl;
			return (1);
		}
		while (std::getline(input, line))
			output << replaceString(line, s1, s2) << std::endl;
		input.close();
		output.close();
	}
	return (0);
}
