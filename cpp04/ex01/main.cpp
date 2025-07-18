/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 16:10:58 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/18 15:55:54 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main()
{
	int n = 100;
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
	for (int i = 0; i < 100; i++)
	{
		std::cout << i << ": ";
		delete animals[i];
	}

	Dog Dog1;
	Dog1.makeSound();

	Dog copyDog = Dog1;
	copyDog.makeSound();
	
	return (0);
}
