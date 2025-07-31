/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 16:10:58 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/31 08:10:39 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main()
{
	std::cout << "\n---Base Animal Tests---\n" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();

	delete (meta);
	delete (j);
	delete (i);

	std::cout << "\n---WrongAnimal Tests---\n" << std::endl;
	const WrongAnimal* wa = new WrongAnimal();
	const WrongAnimal* wc = new WrongCat();
	const WrongCat* wd = new WrongCat();
	
	std::cout << wa->getType() << " " << std::endl;
	std::cout << wc->getType() << " " << std::endl;
	std::cout << wd->getType() << " " << std::endl;
	
	wa->makeSound();
	wc->makeSound();
	wd->makeSound();

	delete (wa);
	delete (wc);
	delete (wd);

	std::cout << "\n---Direct Cat & Dog Usage---\n" << std::endl;
	Cat myCat;
	Dog myDog;
	
	std::cout << myCat.getType() << std::endl;
	std::cout << myDog.getType() << std::endl;
	
	myCat.makeSound();
	myDog.makeSound();

	std::cout << "\n---Copy Constructor and Assignment---\n" << std::endl;
	Cat copyCat(myCat); 
	Dog copyDog;
	
	copyDog = myDog;

	copyCat.makeSound();
	copyDog.makeSound();
	
	return (0);
}