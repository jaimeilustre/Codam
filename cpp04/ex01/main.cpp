/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 16:10:58 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/31 06:25:05 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main()
{
	int n = 4;
	Animal* animals[n];

	std::cout << "\nCreating Dogs and Cats\n";
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

	std::cout << "\nDeleting Animals\n";
	for (int i = 0; i < n; i++)
	{
		std::cout << i << ": ";
		delete animals[i];
	}
	
	std::cout << "\nDeep Copy Test\n";
	Dog originalDog;
	originalDog.makeSound();

	originalDog.setIdea("Chase my tail", 0);
	std::cout << "dog1 idea: " << originalDog.getIdea(0) << std::endl;
	
	Dog copyDog = originalDog;
	copyDog.makeSound();

	copyDog.setIdea("Sleepy sleepy", 0);
	std::cout << "dog2 idea: " << copyDog.getIdea(0) << std::endl;

	std::cout << "originalDog idea[0] after modifying copyDog: " << originalDog.getIdea(0) << std::endl;
	// If originalDog idea is still "Chase my tail", copy is deep
	
	std::cout << "\nPopulate All 100 Ideas\n";
	for (int i = 0; i < 100; ++i)
	{
		std::string idea = "Idea number " + std::to_string(i);
		originalDog.setIdea(idea, i);
		std::cout << "Idea[" << i << "]: " << originalDog.getIdea(i) << std::endl;
	}

	std::cout << "Sample check: idea[42] = " << originalDog.getIdea(42) << std::endl;

	std::cout << "\nTest Out-of-Bounds Idea\n";
	originalDog.setIdea("Shouldn't exist", 100); // index 100 = out of bounds
	std::cout << "Trying to access idea[100]: " << originalDog.getIdea(100) << std::endl;
	
	return (0);
}
