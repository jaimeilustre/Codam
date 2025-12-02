/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/02 11:08:49 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/02 11:20:54 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main(int argc, char **argv)
{
	Data	test;
	test.id = 8;
	test.name = "Jaime";

	std::cout << "Original address: " << &test << std::endl;

	uintptr_t	raw = Serializer::serialize(&test);
	std::cout << "Serialized integer: " << raw << std::endl;

	Data	*restored = Serializer::deserialize(raw);
	std::cout << "Restored address: " << restored << std::endl;

	std::cout << "Original: " << std::endl;
	std::cout << "id = " << restored->id << std::endl;
	std::cout << "name = " << restored->name << std::endl;

	return (0);
}