/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 10:00:21 by jilustre      #+#    #+#                 */
/*   Updated: 2025/08/01 06:11:11 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"

int main(void)
{
	std::cout << "\n---Setup---\n";
	IMateriaSource* src = new MateriaSource();

	AMateria* ice = new Ice();
	src->learnMateria(ice);
	delete ice;

	AMateria* cure = new Cure();
	src->learnMateria(cure);
	delete cure;

	ICharacter* me = new Character("me");

	AMateria* tmp;

	std::cout << "\n---Equip Test (2 Materias)---\n";
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	me->printInventory();
	me->printFloorInventory();

	std::cout << "\n---Use Test (valid)---\n";
	ICharacter* bob = new Character("bob");
	me->use(0, *bob); // shoot ice bolt
	me->use(1, *bob); // heal wounds

	std::cout << "\n---Equip Test (more than 4 slots)---\n";
	AMateria *m3 = src->createMateria("ice");
	AMateria *m4 = src->createMateria("cure");
	AMateria *m5 = src->createMateria("ice");// 5th: should be deleted to avoid leaks
	me->equip(m3);
	me->equip(m4);
	me->equip(m5);
	if (!me->hasInventorySpace())
		delete m5;

	me->printInventory();
	me->printFloorInventory();
	
	std::cout << "\n---Use Test (invalid indexes)---\n";
	me->use(-1, *bob); // nothing should happen
	me->use(4, *bob);  // nothing should happen

	std::cout << "\n---Unequip Test---\n";
	me->unequip(1); // unequip Cure
	me->use(1, *bob); // nothing should happen

	me->printInventory();
	me->printFloorInventory();

	std::cout << "\n---Create Unknown Materia---\n";
	AMateria* unknown = src->createMateria("fire");
	if (!unknown)
		std::cout << "Unknown materia type 'fire'\n";

	std::cout << "\n---Deep Copy Test---\n";
	Character* original = new Character("original");
	original->equip(src->createMateria("ice"));
	original->equip(src->createMateria("cure"));

	original->printInventory();
	original->printFloorInventory();
	

	Character copy = *original; // copy constructor
	std::cout << "[Original uses index 0] ";
	original->use(0, *bob);
	std::cout << "[Copy uses index 0] ";
	copy.use(0, *bob);

	copy.printInventory();
	copy.printFloorInventory();

	delete original;

	std::cout << "\n---Cleanup---\n";
	delete bob;
	delete me;
	delete src;

	return 0;
}


