/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 16:10:58 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/18 17:03:27 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main()
{
	int n = 4;
	Animal* animals[n];

	for (int i = 0; i < n / 2; i++)
	{
		std::cout << i << ": ";
		animals[i] = new Dog();
	}
	for (int i = n / 2; i < n; i++)
	{
		std::cout << i << ": ";
		animals[i] = new Cat();
	}
	for (int i = 0; i < n; i++)
	{
		std::cout << i << ": ";
		delete animals[i];
	}

	Dog originalDog;
	originalDog.makeSound();

	originalDog.getBrain()->setIdea("Picking up stick", 0);
	std::cout << "Original dog idea: " << originalDog.getBrain()->getIdea(0) << std::endl;

	Dog copyDog = originalDog;
	copyDog.makeSound();
	
	return (0);
}
