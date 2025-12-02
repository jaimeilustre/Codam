/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Serializer.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/02 10:41:50 by jilustre      #+#    #+#                 */
/*   Updated: 2025/12/02 10:46:12 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer() {};
Serializer::Serializer(const Serializer& other) {};
Serializer&	Serializer::operator=(const Serializer& other) {};
Serializer::~Serializer() {};

uintptr_t	Serializer::serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data*	Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data*>(raw));
}